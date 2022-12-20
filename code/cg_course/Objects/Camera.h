#ifndef CG_COURSE_CAMERA_H
#define CG_COURSE_CAMERA_H

#include "Matrix.h"
#include "Vec.h"
#include "Transformation.h"

class Camera
{
public:
    Camera() = default;

    Camera(Point3d &origin, Vec3d &dir, Vec3d &up);

    void move(double dx, double dy, double dz);

    void rotate(double dx, double dy, double dz);

    void scale(double dx, double dy, double dz);

public:
    Point3d origin;
    Vec3d dir;
    Vec3d up;
};

#endif
