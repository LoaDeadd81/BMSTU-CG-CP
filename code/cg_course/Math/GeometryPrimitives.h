#ifndef CG_COURSE_GEOMETRYPRIMITIVES_H
#define CG_COURSE_GEOMETRYPRIMITIVES_H

#include "Vec.h"
#include "OBJ_Loader.h"
#include "Transformation.h"
#include "Textures.h"

#define EPS2 1e-2

class Ray
{
public:
    Ray() = default;

    Ray(Point3d origin, Vec3d direction);

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

    void move(Matix4x4d &tr_mtr);

    void rotate(Matix4x4d &tr_mtr);

    void scale(Matix4x4d &tr_mtr);

public:
    Point3d p;
    Point4d pt;
    Vec3d n;
    Vec4d nt;
    double u, v;

};

class Polygon
{
public:
    Polygon() = default;

    Polygon(Vertex p1, Vertex p2, Vertex p3);

    bool intersect(const Ray &ray, double &t, Vec3d &n, int &tex_x, int &tex_y, TextureData &data);

    void move(Matix4x4d &tr_mtr);

    void rotate(Matix4x4d &tr_mtr);

    void scale(Matix4x4d &tr_mtr);

public:
    Vertex p1, p2, p3;
};

Vec4d operator*(Vec4d &v, Matix4x4d &mtr);


#endif
