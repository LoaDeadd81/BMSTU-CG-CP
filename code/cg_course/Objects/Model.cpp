#include "Model.h"

#include <utility>

Sphere::Sphere(Point3d center, double r, Color color, ObjectProperties props)
        : center(std::move(center)), radius(r), color(std::move(color)), properties(props)
{

}

void Sphere::transform(const Matix4x3d &transform_matrix)
{

}

bool Sphere::intersect(const Ray &ray, IntersectionData &data)
{
    Vec3d oc = ray.origin - center;
    double a = ray.direction.len_sqr();
    double half_b = oc & ray.direction;
    double c = oc.len_sqr() - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    data.t = (-half_b - sqrt(discriminant)) / a;
    data.color = color;
    data.p = ray.at(data.t);
    data.n = data.p - center;
    data.n.norm();
    return true;
}

void Sphere::setTexture(const string &path)
{

}

void Sphere::setColor(const Color &&clr)
{
    color = clr;
}

ObjectProperties &Sphere::props()
{
    return properties;
}

Plane::Plane(Vec3d normal, double d, Color color, ObjectProperties props)
        : a(normal[0]), b(normal[1]), c(normal[2]), d(d),
          color(std::move(color)), properties(props)
{
    Vec3d tmp = normal;
    tmp.norm();
    tmp *= -d;
    point = tmp;
    this->normal = std::move(normal);
}

void Plane::transform(const Matix4x3d &transform_matrix)
{

}

bool Plane::intersect(const Ray &ray, IntersectionData &data)
{
    double x = ray.origin[0], y = ray.origin[1], z = ray.origin[2];
    double dot_place = x * a + y * b + z * c + d;

    if (abs(dot_place) < ACC_EPS)
        return false;

    double n_dor_d = normal & ray.direction;

    if (dot_place * n_dor_d >= 0)
        return false;

    data.t = ((point - ray.origin) & normal) / (ray.direction & normal);
    data.p = ray.at(data.t);
    data.n = normal;
    data.color = color;

    return true;
}

void Plane::setTexture(const string &path)
{

}

void Plane::setColor(const Color &&clr)
{
    color = clr;
}

ObjectProperties &Plane::props()
{
    return properties;
}
