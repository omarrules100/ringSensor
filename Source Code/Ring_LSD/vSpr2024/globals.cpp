#include "globals.h"

const uint32_t g_muxPinList[] = { 2, 3, 9, 7 }; //LSB to MSB for 64:1 MUX, Pins on port A, other two controls pins tied to ground for now, providing only 16:1
const uint32_t g_controlPinCount = sizeof(g_muxPinList) / sizeof(uint32_t);
const uint32_t g_sensorCount = 16; //number of sensors available
uint32_t* g_binaryMappingToControlLinePins = nullptr; //as name states
uint16_t* g_muxADCReadings = new uint16_t[g_sensorCount];

uint16_t* g_sensorBaseline = new uint16_t[g_sensorCount];

muxControlPinMap g_muxControlPinMap;
Matrix g_sensorIntensityVector = MatrixRect(g_sensorCount, 1); //1 column vector for intensity readings
Matrix g_sensorPositionMatrix = MatrixRect(g_sensorCount, 2); //2 columns for x and y
Matrix g_sensorPositionPseudoInverseMatrix;