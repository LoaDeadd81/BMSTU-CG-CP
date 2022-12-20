#ifndef CG_COURSE_TRANSFORMATION_H
#define CG_COURSE_TRANSFORMATION_H

#include <cmath>

#include "Vec.h"
#include "Matrix.h"

#define TREPS 1e-6

Matix4x4d getMoveMatrix(double dx, double dy, double dz);

Matix4x4d getScaleMatrix(double dx, double dy, double dz);

Matix4x4d getRotateMatrix(double dx, double dy, double dz);

Vec4d operator*(Vec4d &v, Matix4x4d &mtr);

#endif
