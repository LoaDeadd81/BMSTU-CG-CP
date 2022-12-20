#include "Camera.h"

Camera::Camera(Point3d &origin, Vec3d &dir, Vec3d &up) : origin(origin), dir(dir), up(up)
{
    dir.norm();
    up.norm();
}

void Camera::move(double dx, double dy, double dz)
{
    Matix4x4d tr_matrix = getMoveMatrix(dx, dy, dz);
    Point4d tmp_orig = {origin[0], origin[1], origin[2], 1};
    tmp_orig = tmp_orig * tr_matrix;
    for (int i = 0; i < 3; i++)
        origin[i] = tmp_orig[i];
}

void Camera::rotate(double dx, double dy, double dz)
{
    Matix4x4d tr_matrix = getRotateMatrix(dx, dy, dz);
    Vec4d tmp_dir = {dir[0], dir[1], dir[2], 1},
            tmp_up = {up[0], up[1], up[2], 1};

    tmp_dir = tmp_dir * tr_matrix;
    tmp_up = tmp_up * tr_matrix;

    for (int i = 0; i < 3; i++)
        dir[i] = tmp_dir[i];
    for (int i = 0; i < 3; i++)
        up[i] = tmp_up[i];
}

void Camera::scale(double dx, double dy, double dz)
{

}
