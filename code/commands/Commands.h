#ifndef COMMANDS_H
#define COMMANDS_H

#include "BaseCommand.h"
#include "Coord.h"
#include "Managers.h"
#include "Drawer.h"

class DelObjectCommand : public BaseCommand
{
public:
    DelObjectCommand() = default;
    explicit DelObjectCommand(size_t i);
    virtual ~DelObjectCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
private:
    size_t index;
};

class AddObjectCommand : public BaseCommand
{
public:
    AddObjectCommand() = default;
    explicit AddObjectCommand(shared_ptr<SceneObject> obj);
    virtual ~AddObjectCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
private:
    shared_ptr<SceneObject> object;
};

class ChangeCameraCommand : public BaseCommand
{
public:
    ChangeCameraCommand() = default;
    explicit ChangeCameraCommand(size_t i);
    virtual ~ChangeCameraCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
private:
    size_t index;
};


class LoadObjectCommand : public BaseCommand
{
public:
    LoadObjectCommand() = default;
    explicit LoadObjectCommand(string filename);
    virtual ~LoadObjectCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
protected:
    string filename;
};

class LoadCameraCommand : public LoadObjectCommand
{
public:
    LoadCameraCommand() = default;
    explicit LoadCameraCommand(string filename);
    virtual ~LoadCameraCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
};


class DrawCommand : public BaseCommand
{
public:
    DrawCommand() = default;
    explicit DrawCommand(shared_ptr<BaseDrawer> drawer);
    virtual ~DrawCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
private:
    shared_ptr<BaseDrawer> drawer;
};

class TransformCommand : public BaseCommand
{
public:
    TransformCommand() = default;
    explicit TransformCommand(size_t i, const Coord3d &data, const Coord3d &center = {0, 0, 0});
    virtual ~TransformCommand() override = default;
protected:
    size_t index;
    Coord3d data, center;
};

class MoveCommand : public TransformCommand
{
public:
    MoveCommand() = default;
    explicit MoveCommand(size_t i, const Coord3d &data);
    virtual ~MoveCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
};

class RotateCommand : public TransformCommand
{
public:
    RotateCommand() = default;
    explicit RotateCommand(size_t i, const Coord3d &data, const Coord3d &center);
    virtual ~RotateCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
};

class ScaleCommand : public TransformCommand
{
public:
    ScaleCommand() = default;
    explicit ScaleCommand(size_t i, const Coord3d &data, const Coord3d &center);
    virtual ~ScaleCommand() override =default;
    virtual void execute(shared_ptr<BaseManager> manager) override;
};


#endif
