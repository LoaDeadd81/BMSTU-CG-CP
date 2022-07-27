#ifndef COORD_H
#define COORD_H

class Coord3d
{
public:
    Coord3d() = default;
    Coord3d(double x, double y, double z) : x(x), y(y), z(z) {};
    void setX(double new_x) {x = new_x;};
    void setY(double new_y) {y = new_y;};
    void setZ(double new_z) {z = new_z;};
    double getX() const {return x;};
    double getY() const {return y;};
    double getZ() const {return z;};
private:
    double x, y, z;
};

#endif
