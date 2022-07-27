#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <memory>
#include <cmath>

#include "ObjectVisitor.h"
#include "Coord.h"

using namespace std;

class Dot
{
public:
    Dot()=default;
    explicit Dot(Coord3d coord3D) : pos(coord3D) {};
    Dot(double x, double y, double z) : pos(x, y, z) {};
    ~Dot()=default;
    void setDot(const Coord3d &dot);
    Coord3d getDot() const;
    void move(const Coord3d &transform_data);
    void rotate(const Coord3d &center, const Coord3d &transform_data);
    void scale(const Coord3d &center, const Coord3d &transform_data);

private:
    Coord3d pos;

    void move_to_cente(const Coord3d &center);
    void move_back(const Coord3d &center);
    void yz_rotate(double cx);
    void xz_rotate(double cy);
    void xy_rotate(double cz);
};


class Edge
{
public:
    Edge()=default;
    explicit Edge(size_t start, size_t end) : p1(start), p2(end) {};
    ~Edge()=default;
    void setp1(size_t dot);
    void setp2(size_t dot);
    size_t getp1() const;
    size_t getp2() const;

private:
    size_t p1, p2;
};

#endif
