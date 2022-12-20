#ifndef CG_COURSE_LIGHT_H
#define CG_COURSE_LIGHT_H

#include "Matrix.h"
#include "Vec.h"

class Light
{
public:
    Light() = default;

    Light(const Vec3d &origin, double I, const Color &color);

    void move(double dx, double dy, double dz);

    void rotate(double dx, double dy, double dz);

    void scale(double dx, double dy, double dz);

    void setColor(const Color &color);

    void setI(double i);

public:
    Vec3d origin;
    double I;
    Color color;
    Color comp_color;
};

#endif
