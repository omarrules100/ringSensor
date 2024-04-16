#pragma once
//#include "muxControl.h"
#include "lightArray.h"
#include "matrix.h"
#include <cstdint>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


struct muxControlPinMap;

extern const uint32_t g_muxPinList[]; //LSB to MSB for 64:1 MUX, Pins on port A, other two controls pins tied to ground for now, providing only 16:1
extern const uint32_t g_controlPinCount;
extern const uint32_t g_sensorCount; //number of sensors available
extern uint32_t* g_binaryMappingToControlLinePins; //as name states
extern uint16_t* g_muxADCReadings;
extern uint16_t* g_sensorBaseline;

extern muxControlPinMap g_muxControlPinMap;
extern Matrix g_sensorIntensityVector;
extern Matrix g_sensorPositionMatrix;
extern Matrix g_sensorPositionPseudoInverseMatrix;