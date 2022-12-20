#include "Model.h"

#include <utility>

Sphere::Sphere(Point3d center, double r, Color color, ObjectProperties props)
        : center(std::move(center)), radius(r), color(std::move(color / 255.0)), properties(props)
{
    tdata.need_interpolation = false;
}

Sphere::Sphere(Point3d center, double r)
        : center(std::move(center)), radius(r)
{
    tdata.need_interpolation = false;
}

void Sphere::move(double dx, double dy, double dz)
{
    Vec3d mv = {dx, dy, dz};
    center += mv;
}


void Sphere::rotate(double dx, double dy, double dz)
{
    Matix4x4d mtr = getRotateMatrix(dx, dy, dz);

}

void Sphere::scale(double dx, double dy, double dz)
{
    double k = max(dx, max(dy, dz));
    radius *= k;
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

//    data.t = (-half_b - sqrt(discriminant)) / a;
//    if (data.t < EPS)
//        data.t = (-half_b + sqrt(discriminant)) / a;
    data.t = (-half_b - sqrt(discriminant)) / a;
    data.p = ray.at(data.t);
    data.n = data.p - center;
    data.n.norm();
    if (tdata.need_interpolation)
    {
        int x = (data.n[0] / 2.0 + 0.5) * tdata.width,
                y = (data.n[1] / 2.0 + 0.5) * tdata.height;
        data.color = texture->pixelColor(x, y);
    }
    else
        data.color = color;
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

void Sphere::setTexture(shared_ptr<BaseTexture> &texture)
{
    this->texture = texture;
    tdata = texture->getData();
}

void Sphere::setColor(const Color &clr)
{
    color = clr / 255.0;
    tdata.need_interpolation = false;
}

ObjectProperties &Sphere::props()
{
    return properties;
}

Color Sphere::clr(int x, int y)
{
    if (tdata.need_interpolation)
        return texture->pixelColor(x, y);
    else
        return color;
}

bool Sphere::hasTecture()
{
    return tdata.need_interpolation;
}

shared_ptr<BaseTexture> &Sphere::txtr()
{
    return texture;
}

Point3d &Sphere::cntr()
{
    return center;
}

Plane::Plane(Vec3d normal, double d, Color color, ObjectProperties props)
        : d(d),
          color(std::move(color / 255.0)), properties(props)
{
    tdata.need_interpolation = false;
    Vec3d tmp = normal;
    tmp.norm();
    tmp *= -d;
    point = tmp;
    tnormal = {normal[0], normal[1], normal[2], 1};
    this->normal = std::move(normal);
}

void Plane::move(double dx, double dy, double dz)
{
    d += dz;
}

void Plane::rotate(double dx, double dy, double dz)
{
    Matix4x4d tr_matrix = getRotateMatrix(dx, dy, dz);
    tnormal = tnormal * tr_matrix;
    for (int i = 0; i < 3; i++)
        normal[i] = tnormal[i];
}

void Plane::scale(double dx, double dy, double dz)
{

}

bool Plane::intersect(const Ray &ray, IntersectionData &data)
{
    double x = ray.origin[0], y = ray.origin[1], z = ray.origin[2];
    double dot_place = x * normal[0] + y * normal[1] + z * normal[2] + d;

    if (abs(dot_place) < ACC_EPS)
        return false;

    double n_dor_d = normal & ray.direction;

    if (dot_place * n_dor_d >= 0)
        return false;

    data.t = ((point - ray.origin) & normal) / n_dor_d;
    data.p = ray.at(data.t);
    data.n = normal;
    data.color = color;

    return true;
}

void Plane::setTexture(shared_ptr<BaseTexture> &texture)
{
    this->texture = texture;
    tdata = texture->getData();
}

void Plane::setColor(const Color &clr)
{
    color = clr / 255.0;
    tdata.need_interpolation = false;
}

ObjectProperties &Plane::props()
{
    return properties;
}

Color Plane::clr(int x, int y)
{
    if (tdata.need_interpolation)
        return texture->pixelColor(x, y);
    else
        return color;
}

bool Plane::hasTecture()
{
    return tdata.need_interpolation;
}

shared_ptr<BaseTexture> &Plane::txtr()
{
    return texture;
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
        : color(std::move(color / 255.0)), properties(props)
{
    tdata.need_interpolation = false;
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

    double r = max(max(max_p[2] - min_p[2], max_p[1] - min_p[1]), max_p[0] - min_p[0]);
    Point3d origin = {x, y, z};

    bounding_sphere = Sphere(origin, r);

}

void PolygonalBoundedModel::move(double dx, double dy, double dz)
{
    Matix4x4d tr_mtr = getMoveMatrix(dx, dy, dz);
    for (auto &it: polygons)
        it.move(tr_mtr);
    bounding_sphere.move(dx, dy, dz);
}

void PolygonalBoundedModel::rotate(double dx, double dy, double dz)
{
    Point3d center = bounding_sphere.cntr();
    Matix4x4d tr_mtr = getRotateMatrix(dx, dy, dz),
            to_center = getMoveMatrix(-center[0], -center[1], -center[2]),
            back = getMoveMatrix(center[0], center[1], center[2]);
    for (auto &it: polygons)
    {
        it.move(to_center);
        it.rotate(tr_mtr);
        it.move(back);
    }
}

void PolygonalBoundedModel::scale(double dx, double dy, double dz)
{
    Point3d center = bounding_sphere.cntr();
    Matix4x4d tr_mtr = getScaleMatrix(dx, dy, dz),
            to_center = getMoveMatrix(-center[0], -center[1], -center[2]),
            back = getMoveMatrix(center[0], center[1], center[2]);
    for (auto &it: polygons)
    {
        it.move(to_center);
        it.scale(tr_mtr);
        it.move(back);
    }
    bounding_sphere.scale(dx, dy, dz);
}

bool PolygonalBoundedModel::intersect(const Ray &ray, IntersectionData &data)
{
    if (!bounding_sphere.is_intersect(ray))
        return false;

    double min_t = std::numeric_limits<double>::max(), cur_t = 0;
    int cur_tex_x, cur_tex_y, tex_x, tex_y;
    Vec3d n, cur_n;
    bool flag = false;

    for (auto &it: polygons)
    {
        if (it.intersect(ray, cur_t, cur_n, cur_tex_x, cur_tex_y, tdata) && cur_t < min_t)
        {
            min_t = cur_t;
            n = std::move(cur_n);
            flag = true;
            tex_x = cur_tex_x;
            tex_y = cur_tex_y;
        }
    }

    if (!flag)
        return false;

    data.t = min_t;
    data.p = ray.at(min_t);
    data.n = n;
    if (tdata.need_interpolation)
        data.color = texture->pixelColor(tex_x, tex_y);
    else
        data.color = color;

    return true;
}

void PolygonalBoundedModel::setTexture(shared_ptr<BaseTexture> &texture)
{
    this->texture = texture;
    tdata = texture->getData();
}

void PolygonalBoundedModel::setColor(const Color &clr)
{
    color = clr / 255.0;
    tdata.need_interpolation = false;
}

ObjectProperties &PolygonalBoundedModel::props()
{
    return properties;
}


Color PolygonalBoundedModel::clr(int x, int y)
{
    if (tdata.need_interpolation)
        return texture->pixelColor(x, y);
    else
        return color;
}

bool PolygonalBoundedModel::hasTecture()
{
    return tdata.need_interpolation;
}

shared_ptr<BaseTexture> &PolygonalBoundedModel::txtr()
{
    return texture;
}

IntersectionData &IntersectionData::operator=(IntersectionData &&other) noexcept
{
    p = std::move(other.p);
    t = other.t;
    n = std::move(other.n);
    color = std::move(other.color);
    iter = other.iter;

    return *this;
}
