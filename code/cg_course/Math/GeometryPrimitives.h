#ifndef CG_COURSE_GEOMETRYPRIMITIVES_H
#define CG_COURSE_GEOMETRYPRIMITIVES_H

#include "Vec.h"

class Ray
{
public:
    Ray() = default;

    Ray(const Point3d &origin, const Vec3d &direction);

    Point3d at(double t) const;

public:
    Point3d origin;
    Vec3d direction;
};

class IntersectionData
{
public:
    IntersectionData() = default;
    //todo add fields and constructors
public:
    Color color;
    double t;
};


#endif
