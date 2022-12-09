#include "Model.h"

#include <utility>

Sphere::Sphere(Point3d center, double r, Color color, ObjectProperties props)
        : center(std::move(center)), radius(r), color(std::move(color)), properties(props)
{

}

Sphere::Sphere(Point3d center, double r)
        : center(std::move(center)), radius(r)
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

bool Sphere::is_intersect(const Ray &ray)
{
    Vec3d oc = ray.origin - center;
    double a = ray.direction.len_sqr();
    double half_b = oc & ray.direction;
    double c = oc.len_sqr() - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

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

double min4(double a, double b, double c, double d)
{
    return min(min(a, b), min(c, d));
}

void min(Vec3d &cur_min, const Polygon &p)
{
    cur_min[0] = min4(cur_min[0], p.p1.p[0], p.p2.p[0], p.p3.p[0]);
    cur_min[1] = min4(cur_min[1], p.p1.p[1], p.p2.p[1], p.p3.p[1]);
    cur_min[2] = min4(cur_min[2], p.p1.p[2], p.p2.p[2], p.p3.p[2]);
}

double max4(double a, double b, double c, double d)
{
    return max(max(a, b), max(c, d));
}

void max(Vec3d &cur_max, const Polygon &p)
{
    cur_max[0] = max4(cur_max[0], p.p1.p[0], p.p2.p[0], p.p3.p[0]);
    cur_max[1] = max4(cur_max[1], p.p1.p[1], p.p2.p[1], p.p3.p[1]);
    cur_max[2] = max4(cur_max[2], p.p1.p[2], p.p2.p[2], p.p3.p[2]);
}

PolygonalBoundedModel::PolygonalBoundedModel(const objl::Mesh &mesh, Color color, ObjectProperties props)
        : color(std::move(color)), properties(props)
{
    polygons = vector<Polygon>(mesh.Indices.size() / 3);

    Vec3d min_p = {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                   std::numeric_limits<double>::max()},
            max_p = {std::numeric_limits<double>::min(), std::numeric_limits<double>::min(),
                     std::numeric_limits<double>::min()};

    for (int i = 0; i < mesh.Indices.size() / 3; i++)
    {
        polygons[i] = Polygon(mesh.Vertices[mesh.Indices[3 * i]],
                              mesh.Vertices[mesh.Indices[3 * i + 1]],
                              mesh.Vertices[mesh.Indices[3 * i + 2]]);

        min(min_p, polygons[i]);
        max(max_p, polygons[i]);
    }

    double x = min_p[0] + (max_p[0] - min_p[0]) / 2.0,
            y = min_p[1] + (max_p[1] - min_p[1]) / 2.0,
            z = min_p[2] + (max_p[2] - min_p[2]) / 2.0;

    double r = max(max(max_p[2] - min_p[2], max_p[1] - min_p[1]), max_p[0] - min_p[0]) / 2.0;
    Point3d origin = {x, y, z};

    bounding_sphere = Sphere(origin, r);

}

void PolygonalBoundedModel::transform(const Matix4x3d &transform_matrix)
{

}

bool PolygonalBoundedModel::intersect(const Ray &ray, IntersectionData &data)
{
    if (!bounding_sphere.is_intersect(ray))
        return false;

    //todo
    return false;

}

void PolygonalBoundedModel::setTexture(const string &path)
{

}

void PolygonalBoundedModel::setColor(const Color &&clr)
{
    color = clr;
}

ObjectProperties &PolygonalBoundedModel::props()
{
    return properties;
}
