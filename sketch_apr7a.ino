#include "globals.h"
#include "matrix.h"
#include "muxControl.h"
#include "lightArray.h"

uint32_t activeSensor;
float* testIntensityReadings;

void setup() {
  // put your setup code here, to run once:

	activeSensor= 0; //currently selected sensor
	testIntensityReadings = nullptr; //initialize test intensity readings
	lightArrayInit(activeSensor); //initialize mux controls
  Serial.begin(9600);
  analogReadResolution(16);
  pinMode(D5, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  lightArrayBaseline(); //take baseline
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //lightArrayTestOne(testIntensityReadings); //sample sensors 1 second apart
	lightArraySampleSensors();
  //muxControlReadPins(g_muxControlPinMap, g_binaryMappingToControlLinePins, g_muxADCReadings, activeSensor, g_sensorCount);
  //lightArraySelectSensor(g_muxControlPinMap, g_binaryMappingToControlLinePins, 0b0101);
  //delay(5000);
  //lightArraySelectSensor(g_muxControlPinMap, g_binaryMappingToControlLinePins, 0b1010);
  //delay(5000);
  //digitalWrite(D5, HIGH);
  for (int i = 0; i < 16; i++)
  {
  Serial.print("Sensor[");
  Serial.print(i);
  Serial.print("]: ");
  Serial.print(100*g_sensorIntensityVector.element[i][0],5);
  Serial.print("% - ");
  Serial.print(g_muxADCReadings[i]);
  }
  Serial.println(lightArrayCalculateAoAD(),32);
  // Serial.println("Sensor[1]: ");
  // Serial.println(testIntensityReadings[1],32);
  // Serial.println("Sensor[2]: ");
  // Serial.println(testIntensityReadings[2],32);
  // Serial.println("Sensor[3]: ");
  // Serial.println(testIntensityReadings[3],32);
  // Serial.println("Sensor[4]: ");
  // Serial.println(testIntensityReadings[4],32);
  // Serial.println("Sensor[5]: ");
  // Serial.println(testIntensityReadings[5],32);
  // Serial.println("Sensor[6]: ");
  // Serial.println(testIntensityReadings[6],32);
  // Serial.println("Sensor[7]: ");
  // Serial.println(testIntensityReadings[7],32);
  // Serial.println("Sensor[8]: ");
  // Serial.println(testIntensityReadings[8],32);
  // Serial.println("Sensor[9]: ");
  // Serial.println(testIntensityReadings[9],32);
  // Serial.println("Sensor[10]: ");
  // Serial.println(testIntensityReadings[10],32);
  // Serial.println("Sensor[11]: ");
  // Serial.println(testIntensityReadings[11],32);
  // Serial.println("Sensor[12]: ");
  // Serial.println(testIntensityReadings[12],32);
  // Serial.println("Sensor[13]: ");
  // Serial.println(testIntensityReadings[13],32);
  // Serial.println("Sensor[14]: ");
  // Serial.println(testIntensityReadings[14],32);
  // Serial.println("Sensor[15]: ");
  // Serial.println(testIntensityReadings[15],32);
}
