#include "GeometryPrimitives.h"

Ray::Ray(const Point3d &origin, const Vec3d &direction) : origin(origin), direction(direction)
{

}

Point3d Ray::at(double t) const
{
    return origin + t * direction;
}
