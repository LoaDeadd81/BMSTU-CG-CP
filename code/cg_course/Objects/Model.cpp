#include "Model.h"

Sphere::Sphere(Point3d center, double r, Color color, ObjectProperties props) : center(center), radius(r), color(color),
                                                                                properties(props)
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
