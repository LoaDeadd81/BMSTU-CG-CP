#ifndef CAMERA_H
#define CAMERA_H

#include "SimpleObject.h"
#include "Coord.h"
#include "primitives.h"
#include <cmath>

class CameraBuilder;
class DrawVisitor;

class Camera : public InvisibleObject
{
    friend CameraBuilder;
    friend DrawVisitor;
public:
    Camera() = default;
    Camera(const Dot &position, const Coord3d &direction) : pos(position), angles(direction) {};
    virtual ~Camera() override = default;
    virtual bool isViewer() const override ;
    virtual void accept(shared_ptr<ObjectVisitor> visitor) override;
    virtual void move(const Coord3d &transform_data) override;
    virtual void rotate(const Coord3d &transform_data, const Coord3d &center) override;
    virtual void scale(const Coord3d &transform_data, const Coord3d &center) override;
    virtual void rotate(const Coord3d &transform_data) override;
    virtual void scale(const Coord3d &transform_data) override;
    virtual Coord3d get_center() override;

private:
    Dot pos;
    Coord3d angles;

    Dot getPos() const;
    Coord3d getDir() const;
    void setPos(Dot &position);
    void setDir(Coord3d &direction);
};


#endif
