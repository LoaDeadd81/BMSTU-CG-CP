#include "GeometryPrimitives.h"

#include <utility>

//Vec4d operator*(Vec4d &v, Matix4x4d &mtr)
//{
//    Vec4d res;
//    for (int i = 0; i < 4; i++)
//    {
//        for (int j = 0; j < 4; j++)
//        {
//            res[i] += mtr[j][i] * v[j];
//        }
//    }
//
//    return res;
//}

Ray::Ray(Point3d origin, Vec3d direction) : origin(origin), direction(direction)
{

}

Point3d Ray::at(double t) const
{
    return origin + t * direction;
}

Vertex::Vertex(Point3d p, Vec3d n, double u, double v)
        : u(u), v(v)
{
    pt = {p[0], p[1], p[2], 1};
    nt = {n[0], n[1], n[2], 1};
    this->p = std::move(p);
    this->n = std::move(n);
}

Vertex::Vertex(const objl::Vertex &v)
{
    p = {v.Position.X, v.Position.Y, v.Position.Z};
    pt = {p[0], p[1], p[2], 1};
    n = {v.Normal.X, v.Normal.Y, v.Normal.Z};
    nt = {n[0], n[1], n[2], 1};
    u = v.TextureCoordinate.X;
    this->v = v.TextureCoordinate.Y;
}

void Vertex::move(Matix4x4d &tr_mtr)
{
    pt = pt * tr_mtr;
    for (int i = 0; i < 3; i++)
        p[i] = pt[i];
}

void Vertex::rotate(Matix4x4d &tr_mtr)
{
    pt = pt * tr_mtr;
    for (int i = 0; i < 3; i++)
        p[i] = pt[i];

    nt = nt * tr_mtr;
    for (int i = 0; i < 3; i++)
        n[i] = nt[i];
}

void Vertex::scale(Matix4x4d &tr_mtr)
{
    pt = pt * tr_mtr;
    for (int i = 0; i < 3; i++)
        p[i] = pt[i];

    nt = nt * tr_mtr;
    for (int i = 0; i < 3; i++)
        n[i] = nt[i];
}

Polygon::Polygon(Vertex p1, Vertex p2, Vertex p3)
        : p1(std::move(p1)), p2(std::move(p2)), p3(std::move(p3))
{

}

bool Polygon::intersect(const Ray &ray, double &t, Vec3d &n, int &tex_x, int &tex_y, TextureData &data)
{
    Vec3d e1 = p2.p - p1.p, e2 = p3.p - p1.p;
    Vec3d pvec = ray.direction ^ e2;
    double det = e1 & pvec;

    if (abs(det) < EPS2)
        return false;

    double inv_det = 1.0 / det;
    Vec3d tvec = ray.origin - p1.p;
    double u = (tvec & pvec) * inv_det;
    if (u < 0 || u > 1)
        return false;

    Vec3d qvec = tvec ^ e1;
    double v = (ray.direction & qvec) * inv_det;
    if (v < 0 || u + v > 1)
        return false;

    t = (e2 & qvec) * inv_det;
    n = p2.n * u + p3.n * v + p1.n * (1 - u - v);
    n.norm();

    if (data.need_interpolation)
    {
        double p_u = p2.u * u + p3.u * v + p1.u * (1 - u - v),
                p_v = p2.v * u + p3.v * v + p1.v * (1 - u - v);
        tex_x = p_u * (data.width - 1);
        tex_y = p_v * (data.height - 1);
    }

    return true;
}

void Polygon::move(Matix4x4d &tr_mtr)
{
    p1.move(tr_mtr);
    p2.move(tr_mtr);
    p3.move(tr_mtr);
}

void Polygon::rotate(Matix4x4d &tr_mtr)
{
    p1.rotate(tr_mtr);
    p2.rotate(tr_mtr);
    p3.rotate(tr_mtr);
}

void Polygon::scale(Matix4x4d &tr_mtr)
{
    p1.scale(tr_mtr);
    p2.scale(tr_mtr);
    p3.scale(tr_mtr);
}
