#ifndef CG_COURSE_TRANSFORMATION_H
#define CG_COURSE_TRANSFORMATION_H

#include "Vec.h"
#include "Matrix.h"

Matix4x3d getMoveMatrix(Vec3d data);

Matix4x3d getScaleMatrix(Vec3d data);

Matix4x3d getRotateMatrix(Vec3d data);

#endif
