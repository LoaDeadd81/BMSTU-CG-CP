#ifndef CG_COURSE_CAMERA_H
#define CG_COURSE_CAMERA_H

#include "Matrix.h"

class BaseCamera
{
public:
    virtual void transform(const Matix4x3d &transform_matrix) = 0;
};

#endif
