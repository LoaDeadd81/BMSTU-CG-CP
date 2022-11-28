#ifndef CG_COURSE_LIGHT_H
#define CG_COURSE_LIGHT_H

#include "Matrix.h"

class BaseLight
{
public:
    virtual void transform(const Matix4x3d &transform_matrix) = 0;
};

#endif
