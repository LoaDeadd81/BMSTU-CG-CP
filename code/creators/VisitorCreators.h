#ifndef VISITORCREATORS_H
#define VISITORCREATORS_H

#include "TransformVisitor.h"
#include "DrawVisitor.h"

class MoveVisitorCreator
{
public:
    shared_ptr<ObjectVisitor> create(const Coord3d &data);
};

class RotateVisitorCreator
{
public:
    shared_ptr<ObjectVisitor> create(const Coord3d &data, const Coord3d &center = {0, 0, 0});
};

class ScaleVisitorCreator
{
public:
    shared_ptr<ObjectVisitor> create(const Coord3d &data, const Coord3d &center = {0, 0, 0});
};

class DrawVisitorCreator
{
public:
    shared_ptr<ObjectVisitor> create(shared_ptr<BaseDrawer> drawer, shared_ptr<Camera> camera);
};

#endif
