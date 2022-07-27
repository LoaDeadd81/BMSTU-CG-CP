#include "Camera.h"

void Camera::accept(shared_ptr<ObjectVisitor> visitor)
{
    visitor->visit(*this);
}

Dot Camera::getPos() const
{
    return pos;
}

Coord3d Camera::getDir() const
{
    return angles;
}

void Camera::setPos(Dot &position)
{
    pos = position;
}

void Camera::setDir(Coord3d &direction)
{
    angles = direction;
}

bool Camera::isViewer() const
{
    return true;
}

void Camera::move(const Coord3d &transform_data)
{
    pos.move(transform_data);
}

void Camera::rotate(const Coord3d &transform_data, const Coord3d &center)
{
    pos.rotate(center, transform_data);
}

void Camera::scale(const Coord3d &transform_data, const Coord3d &center)
{
    pos.scale(center, transform_data);
}

void Camera::rotate(const Coord3d &transform_data)
{
    double new_x = fmod(angles.getX() + transform_data.getX(), 360),
            new_y = fmod(angles.getY() + transform_data.getY(), 360),
            new_z = fmod(angles.getZ() + transform_data.getZ(), 360);
    angles = {new_x, new_y, new_z};
}

void Camera::scale(const Coord3d &transform_data)
{

}

Coord3d Camera::get_center()
{
    return pos.getDot();
}


