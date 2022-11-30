#ifndef CG_COURSE_LIGHT_H
#define CG_COURSE_LIGHT_H

#include "Matrix.h"
#include "Vec.h"

class Light
{
public:
    Light() = default;

    Light(Vec3d origin, double I);

    virtual void transform(const Matix4x3d &transform_matrix);

public:
    Vec3d origin;
    double I;
};

#endif
