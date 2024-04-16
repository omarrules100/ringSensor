#pragma once
#include <cstdint>
#include <cmath>
#include "globals.h"
#include "Arduino.h"

struct muxControlPinMap {
	uint8_t* muxPinDec; //decimal value that indicates what pin it is
	uint32_t* muxPin; //bit associated with mux control pin, on port A, indexed by LSB(muxBit[0]) to MSB(muxBit[muxPinCount-1])
	uint32_t muxPins; //bits associated with all mux control pins, on port A
	uint32_t muxPinCount;
};



//void muxControlAddSensor(int bit);

//void muxControlAddControlPin(int bit); //adds one pin at a time

muxControlPinMap muxControlInit(uint32_t** decimalBinaryMapping, uint32_t& activeSensor, const uint32_t* muxPinList, const uint32_t controlPinCount, const uint32_t sensorCount);

void muxControlAddControlPins(muxControlPinMap& controlPinMap, const uint32_t* bits, const uint32_t arr_length); //adds list of pins from a constant uin32_t array

uint16_t muxControlReadPin(void);

void muxControlNextSensor(muxControlPinMap& controlPinMap, uint32_t& muxControlValue);

void muxControlWriteControlPins(const muxControlPinMap controlPinMap, const uint32_t muxSelectedControlLines);

uint32_t muxControlMapToBinary(const muxControlPinMap controlPinMap, const uint32_t value);

uint32_t* muxControlBinaryMapping(const muxControlPinMap controlPinMap, const uint32_t sensorCount);

void muxControlReadPins(const muxControlPinMap controlPinMap, const uint32_t* decimalBinaryMapping, uint16_t*& ADC_reading, uint32_t& activeSensor, const uint32_t sensorCount);

