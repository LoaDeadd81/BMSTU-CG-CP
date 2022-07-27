#ifndef MANAGERS_H
#define MANAGERS_H

#include "BaseManager.h"
#include "Coord.h"
#include "VisitorCreators.h"
#include "DrawTools.h"
#include "FabricSolution.h"
#include "Drawer.h"
#include "Builder.h"
#include "Solution.h"
#include "Creator.h"
#include "Error.h"


class AddObjectManager : public BaseManager
{
public:
    AddObjectManager() = default;
    AddObjectManager(shared_ptr<BaseScene> scene);
    virtual ~AddObjectManager() override = default;
    void execute(shared_ptr<SceneObject> obj);
};

class DelObjectManager : public BaseManager
{
public:
    DelObjectManager() = default;
    DelObjectManager(shared_ptr<BaseScene> scene);
    virtual ~DelObjectManager() override = default;
    void execute(size_t i);
};

class ChangeCameraManager : public BaseManager
{
public:
    ChangeCameraManager() = default;
    ChangeCameraManager(shared_ptr<BaseScene> scene);
    virtual ~ChangeCameraManager() override = default;
    void execute(size_t i);
};

class LoadObjectManager : public BaseManager
{
public:
    LoadObjectManager() = default;
    explicit LoadObjectManager(shared_ptr<BaseScene> scene);
    virtual ~LoadObjectManager() override =default;
    void execute(string &filename);
};

class LoadCameraManager : public BaseManager
{
public:
    LoadCameraManager() = default;
    explicit LoadCameraManager(shared_ptr<BaseScene> scene);
    virtual ~LoadCameraManager() override =default;
    void execute(string &filename);
};


class DrawManager : public BaseManager
{
public:
    DrawManager() = default;
    explicit DrawManager(shared_ptr<BaseScene> scene);
    virtual ~DrawManager() override =default;
    void execute(shared_ptr<BaseDrawer> drawer);
};

class MoveManager : public BaseManager
{
public:
    MoveManager() = default;
    MoveManager(shared_ptr<BaseScene> scene);
    virtual ~MoveManager() override = default;
    void execute(size_t i, const Coord3d &data);
};

class RotateManager : public BaseManager
{
public:
    RotateManager() = default;
    RotateManager(shared_ptr<BaseScene> scene);
    virtual ~RotateManager() override = default;
    void execute(size_t i, const Coord3d &data, const Coord3d &center);
};

class ScaleManager : public BaseManager
{
public:
    ScaleManager() = default;
    ScaleManager(shared_ptr<BaseScene> scene);
    virtual ~ScaleManager() override = default;
    void execute(size_t i, const Coord3d &data, const Coord3d &center = {0, 0, 0});
};
#endif
