#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include "BaseScene.h"

class BaseManager
{
public:
    BaseManager() = default;
    explicit BaseManager(shared_ptr<BaseScene> scene) : scene(scene) {};
    virtual ~BaseManager() = default ;
protected:
    shared_ptr<BaseScene> scene;
};

#endif
