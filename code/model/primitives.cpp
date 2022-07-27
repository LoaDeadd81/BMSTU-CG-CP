#include "primitives.h"

double degree_to_radians(double degree)
{
    return degree * (M_PI / 180.0);
}

void Dot::setDot(const Coord3d &dot)
{
    pos = dot;
}

Coord3d Dot::getDot() const
{
    return pos;
}

void Dot::move(const Coord3d &transform_data)
{
    double new_x = pos.getX() + transform_data.getX(),
            new_y = pos.getY() + transform_data.getY(),
            new_z = pos.getZ() + transform_data.getZ();
    pos = {new_x, new_y, new_z};
}

void Dot::rotate(const Coord3d &center, const Coord3d &transform_data)
{
    move_to_cente(center);

    yz_rotate(transform_data.getX());
    xz_rotate(transform_data.getY());
    xy_rotate(transform_data.getZ());

    move_back(center);
}

void Dot::scale(const Coord3d &center, const Coord3d &transform_data)
{
    double new_x = transform_data.getX() * pos.getX() + (1 - transform_data.getX()) * center.getX(),
            new_y = transform_data.getY() * pos.getY() + (1 - transform_data.getY()) * center.getY(),
            new_z = transform_data.getZ() * pos.getZ() + (1 - transform_data.getZ()) * center.getZ();
    pos = {new_x, new_y, new_z};
}

void Dot::move_to_cente(const Coord3d &center)
{
    Coord3d data = {-center.getX(), -center.getY(), -center.getZ()};
    move(data);
}

void Dot::move_back(const Coord3d &center)
{
    Coord3d data = {center.getX(), center.getY(), center.getZ()};
    move(data);
}

void Dot::yz_rotate(double cx)
{
    double radians = degree_to_radians(cx);
    double tmp_y = pos.getY(), tmp_z = pos.getZ();
    pos.setY(tmp_y * cos(radians) - tmp_z * sin(radians));
    pos.setZ(tmp_y * sin(radians) + tmp_z * cos(radians));
}

void Dot::xz_rotate(double cy)
{
    double radians = degree_to_radians(cy);
    double tmp_x = pos.getX(), tmp_z = pos.getZ();
    pos.setX(tmp_x * cos(radians) + tmp_z * sin(radians));
    pos.setZ(-tmp_x * sin(radians) + tmp_z * cos(radians));
}

void Dot::xy_rotate(double cz)
{
    double radians = degree_to_radians(cz);
    double tmp_y = pos.getY(), tmp_x = pos.getX();
    pos.setX(tmp_x * cos(radians) - tmp_y * sin(radians));
    pos.setY(tmp_x * sin(radians) + tmp_y * cos(radians));
}

void Edge::setp1(size_t dot)
{
    p1 = dot;
}

void Edge::setp2(size_t dot)
{
    p2 = dot;
}

size_t Edge::getp1() const
{
    return p1;
}

size_t Edge::getp2() const
{
    return p2;
}


