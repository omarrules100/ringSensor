#include "muxControl.h"

muxControlPinMap muxControlInit(uint32_t** decimalBinaryMapping, uint32_t& activeSensor, const uint32_t* muxPinList, const uint32_t controlPinCount, const uint32_t sensorCount)
{
	muxControlPinMap activeControlPins; //create control pin map
	activeControlPins.muxPin = nullptr;
	activeControlPins.muxPinDec = nullptr;
	activeControlPins.muxPinCount = 0;
	activeControlPins.muxPins = 0;
	muxControlAddControlPins(activeControlPins, muxPinList, controlPinCount); //load up mux control pin mappings with decimal mapping to one-hot
	*decimalBinaryMapping = muxControlBinaryMapping(activeControlPins, sensorCount); //this maps the sensors to the muxes control lines of the pin mappings
	activeSensor = (uint32_t)0; //initialize control pin signals
	muxControlWriteControlPins(activeControlPins, *decimalBinaryMapping[activeSensor]); //initial control pin signals asserted
	return activeControlPins;
}


void muxControlAddControlPins(muxControlPinMap &controlPinMap, const uint32_t* bits, const uint32_t arr_length)
{

	if (controlPinMap.muxPin != nullptr || controlPinMap.muxPinDec != nullptr) //if had mux pins assigned before, delete them
	{
		if (controlPinMap.muxPin != nullptr)
		{
			delete[] controlPinMap.muxPin;
			controlPinMap.muxPin = nullptr;
		}
		if (controlPinMap.muxPinDec != nullptr)
		{
			delete[] controlPinMap.muxPinDec;
			controlPinMap.muxPinDec = nullptr;
		}
	}
	controlPinMap.muxPinCount = arr_length;
	controlPinMap.muxPins = (uint32_t)0;
	controlPinMap.muxPin = new uint32_t[controlPinMap.muxPinCount];
	controlPinMap.muxPinDec = new uint8_t[controlPinMap.muxPinCount];

	uint32_t i = 0;
	for (i = 0; i < controlPinMap.muxPinCount; i++)
	{
		controlPinMap.muxPinDec[i] = bits[i]; //store the decimal value that indicates the pin
		controlPinMap.muxPin[i] = ((uint32_t)1) << controlPinMap.muxPinDec[i];//shift over 1 into the bit position, then add the result to the of muxs control pins list
		controlPinMap.muxPins |= controlPinMap.muxPin[i]; //add mux control pin to all mux control pins 
	}

	return;
}

uint16_t muxControlReadPin(void)
{
	return analogRead(A11); //GIGA's analog resolutions are 16 bit
}

//selects the next sensor
//not used. Could be used if generalized. make g_sensorCount a parameter
void inline muxControlNextSensor(muxControlPinMap& controlPinMap, uint32_t& muxControlValue)
{
	if (muxControlValue >= g_sensorCount - 1)
		muxControlValue = 0;
	else
		muxControlValue++;
	muxControlWriteControlPins(controlPinMap, muxControlValue);
}

void muxControlWriteControlPins(const muxControlPinMap controlPinMap, const uint32_t muxSelectedControlLines)
{
	//input validation is not done, to decrease delay
	//if (controlPinMap.muxPin == nullptr || controlPinMap.muxPinDec == nullptr || controlPinMap.muxPinCount == 0)
		//return;
	GPIOA->ODR &= ~controlPinMap.muxPins;//clear all control bits
	GPIOA->ODR |= muxSelectedControlLines; //assert/deassert the control bits
}

//maps a decimal value to the binary control bits, LSB to MSB
uint32_t muxControlMapToBinary(const muxControlPinMap controlPinMap, const uint32_t value)
{
	//value is in binary, now we need to shift all the bits to the right place

	if (controlPinMap.muxPin == nullptr || controlPinMap.muxPinDec == nullptr || controlPinMap.muxPinCount == 0)
		return 0xFFFFFFFF; //all ones for error
	uint32_t bit; //current bit value at index i
	uint32_t controlBits = 0; //current control bits
	for (int i = 0; i < controlPinMap.muxPinCount; i++)
	{
		bit = value >> i;//controlPinMap.muxPinDec[i]; //shift by the position of the ith control bit
		bit <<= controlPinMap.muxPinDec[i];
		bit &= controlPinMap.muxPin[i]; //isolates the shifted bit
		controlBits |= bit; //adds the shifted bit to the control bits
	}
	return controlBits;
}

//maps all decimal values to the binary control bits, LSB to MSB
uint32_t* muxControlBinaryMapping(const muxControlPinMap controlPinMap, const uint32_t sensorCount)
{
	//value is in binary, now we need to shift all the bits to the right place

	if (controlPinMap.muxPin == nullptr || controlPinMap.muxPinDec == nullptr || controlPinMap.muxPinCount == 0)
		return nullptr;
	uint32_t* mappings = new uint32_t[sensorCount];
	uint32_t i = 0;
	for (i = 0; i < sensorCount; i++)
	{
		mappings[i] = muxControlMapToBinary(controlPinMap, i);
		if (mappings[i] == 0xFFFFFFFF)
		{
			delete[] mappings;
			return nullptr;
		}
	}
	return mappings;
}

void muxControlReadPins(const muxControlPinMap controlPinMap, const uint32_t* decimalBinaryMapping, uint16_t* &ADC_reading, uint32_t &activeSensor, const uint32_t sensorCount)
{
	if (ADC_reading == nullptr)
		ADC_reading = new uint16_t[sensorCount];
	uint32_t i = 0;
	//float temp[] = { 0.866025403784439, 0.991444861373811, 0.965925826289068 ,0.793353340291235, 0.500000000000000,0.130526192220052,0,0,0,0,0,0,0,0,0.258819045102521,0.608761429008721 };

	for (i = 0; i < sensorCount; i++)
	{
		/*
		When VEE is grounded:
		Max propagation delay of two HCT Muxes in series: 24 ns
		Max frequency of two HCT Muxes in series: 41.67 MHz

		When VEE is a negative volt source:
		Max propagation delay of two HCT Muxes in series: 16 ns
		Max frequency of two HCT Muxes in series: 62.50 MHz 
		*/

		muxControlWriteControlPins(controlPinMap, decimalBinaryMapping[i]); //assert new control line values
		//for (int j = 0; j < 2; j++) //we require 24 ns to account for max propagation, there is about 6 cycles per loop = 12.5 ns, so require 2 loops for total of 25 ns
		delayMicroseconds(400000);
    //asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); //delays for one clock cycle, aka 2.083ns if 480 MHz [asm volatile("nop")] <--In arduino sketches
		//asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop");
		ADC_reading[i] = muxControlReadPin();//(uint16_t)(temp[i] * 65535);//muxControlReadPin();//(uint16_t)(temp[i] * 65535);//muxControlReadPin(); //read adc reading
	}
	activeSensor = i - 1;

	return;
}
