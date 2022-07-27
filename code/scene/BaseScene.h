#ifndef BASESCENE_H
#define BASESCENE_H

#include <list>

#include "SceneObjects.h"

class BaseScene
{
public:
    BaseScene() = default;
    virtual ~BaseScene() = default;
    virtual size_t get_size() const = 0;
    virtual shared_ptr<Camera> get_cam() const = 0;
    virtual void set_cam(size_t i) = 0;
    virtual void add_object(shared_ptr<SceneObject> obj) = 0;
    virtual void del_object(size_t i) = 0;
    virtual list<shared_ptr<SceneObject>>::iterator begin() = 0;
    virtual list<shared_ptr<SceneObject>>::iterator end() = 0;
protected:
    list<shared_ptr<SceneObject>> objects;
    list<shared_ptr<SceneObject>>::iterator cur_camera;
};

#endif
