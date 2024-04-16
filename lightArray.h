#pragma once

#include "matrix.h"
#include "muxControl.h"
#include "globals.h"
#include <cmath>
#include "coordConversion.h"
#include <cstdint>

struct muxControlPinMap;

struct sensorMap {
	uint32_t* sensorBit; //bit associated with sensor, on port A
	uint32_t sensorBits; //bits associated with all sensors, on port A
	int sensorCount;
};

void lightArrayInit(uint32_t& binaryControlLineValue);

float lightArrayCalculateAoAD();

void lightArraySampleSensors();

void lightArraySelectSensor(const muxControlPinMap& controlPinMap, uint32_t* const& decimalBinaryMapping, const uint32_t selectedSensor);

uint16_t inline lightArraySampleSensor(const muxControlPinMap& controlPinMap, uint32_t* const& decimalBinaryMapping, const uint32_t selectedSensor);

uint32_t lightArraySampleSelectedSensors(const muxControlPinMap& controlPinMap, uint32_t* const& decimalBinaryMapping, uint32_t* const& selectedSensors, const uint32_t& sensorCount, float* const& intensityReadings);

void lightArrayReMapArrayValues(float* const& reMappedValues, uint16_t* const& originalValues, const uint32_t& numberToRemap);

void lightArrayTestOne(float* &intensityReadings);

void lightArrayTestTwo(float* &intensityReadings);

void lightArrayTestTwo();

Matrix lightArrayCreateSensorPositionRING(float radius, uint32_t sensorCount);

Matrix lightArraySensorPositionPseudoInverse(const Matrix& sensorPositionMatrix);

float lightArrayAoAD(const Matrix& sensorPositionPseudoInverseMatrix, const Matrix& sensorIntensityVector);

void lightArrayBaseline();

void inline lightArrayDelayTwentyFiveNano();

void inline lightArrayDelayMicroTenth();

void inline lightArrayDelayMicro();

void inline lightArrayDelayMilliHundreth();

void inline lightArrayDelayMilliTenth();

void inline lightArrayDelayMilli();

void inline lightArrayDelaySecondHundreth();

void inline lightArrayDelaySecondTenth();

void inline lightArrayDelaySecond();

template <typename T> float lightArrayReMapADC(T min, T max, T value);