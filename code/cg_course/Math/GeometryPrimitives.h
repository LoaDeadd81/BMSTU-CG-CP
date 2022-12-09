#ifndef CG_COURSE_GEOMETRYPRIMITIVES_H
#define CG_COURSE_GEOMETRYPRIMITIVES_H

#include "Vec.h"
#include "OBJ_Loader.h"


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

class Vertex
{
public:
    Vertex() = default;

    Vertex(Point3d p, Vec3d n, double u, double v);

    Vertex(const objl::Vertex &v);

public:
    Point3d p;
    Vec3d n;
    double u, v;

};

class Polygon
{
public:
    Polygon() = default;

    Polygon(Vertex p1, Vertex p2, Vertex p3);

    bool intersect(const Ray &ray, double &t, Vec3d &n);

public:
    Vertex p1, p2, p3;
};

#endif
