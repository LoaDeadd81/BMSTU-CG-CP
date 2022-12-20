#include "Light.h"

#include <utility>

Light::Light(const Vec3d &origin, double I, const Color &color) : origin(origin), I(I), color(color / 255.0)
{
    comp_color = this->color * I;
}

void Light::move(double dx, double dy, double dz)
{
    Vec3d data = {dx, dy, dz};
    origin += data;
}

void Light::rotate(double dx, double dy, double dz)
{

}

void Light::scale(double dx, double dy, double dz)
{

}

void Light::setColor(const Color &color)
{
    this->color = color / 255.9;
    comp_color = this->color * I;
}

void Light::setI(double i)
{
    this->I = i;
    comp_color = color * I;
}
