#include "GeometryPrimitives.h"

#include <utility>

Ray::Ray(const Point3d &origin, const Vec3d &direction) : origin(origin), direction(direction)
{

}

Point3d Ray::at(double t) const
{
    return origin + t * direction;
}

Vertex::Vertex(Point3d p, Vec3d n, double u, double v)
        : p(std::move(p)), n(std::move(n)), u(u), v(v)
{

}

Vertex::Vertex(const objl::Vertex &v)
{
    p = {v.Position.X, v.Position.Y, v.Position.Z};
    n = {v.Normal.X, v.Normal.Y, v.Normal.Z};
    u = v.TextureCoordinate.X;
    this->v = v.TextureCoordinate.Y;
}

Polygon::Polygon(Vertex p1, Vertex p2, Vertex p3)
        : p1(std::move(p1)), p2(std::move(p2)), p3(std::move(p3))
{

}

bool Polygon::intersect(const Ray &ray, double &t, Vec3d &n)
{
    return false;
}
