#pragma once

#include <cmath>
#include "matrix.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


Matrix cart2Sph(const Matrix& cartesian);

Matrix cart2SphD(const Matrix& cartesian);

Matrix cart2Pol(const Matrix& cartesian);

Matrix cart2PolD(const Matrix& cartesian);

Matrix sphRad2Deg(const Matrix& radian);

Matrix polRad2Deg(const Matrix& radian);
