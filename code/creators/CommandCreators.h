#ifndef COMMANDCREATORS_H
#define COMMANDCREATORS_H

#include "Commands.h"

class DelObjectCommandCreator
{
public:
    shared_ptr<BaseCommand> create(size_t i);
};

class AddObjectCommandCreator
{
public:
    shared_ptr<BaseCommand> create(shared_ptr<SceneObject> obj);
};

class ChangeCameraCommandCreator
{
public:
    shared_ptr<BaseCommand> create(size_t i);
};

class LoadObjectCommandCreator
{
public:
    shared_ptr<BaseCommand> create(string filename);
};

class LoadCameraCommandCreator
{
public:
    shared_ptr<BaseCommand> create(string filename);
};

class DrawCommandCreator
{
public:
    shared_ptr<BaseCommand> create(shared_ptr<BaseDrawer> drawer);
};

class MoveCommandCreator
{
public:
    shared_ptr<BaseCommand> create(size_t i, const Coord3d &data);
};

class RotateCommandCreator
{
public:
    shared_ptr<BaseCommand> create(size_t i, const Coord3d &data, const Coord3d &center = {0, 0, 0});
};

class ScaleCommandCreator
{
public:
    shared_ptr<BaseCommand> create(size_t i, const Coord3d &data, const Coord3d &center = {0, 0, 0});
};

#endif
