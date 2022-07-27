#ifndef SCENEOBJECTS_H
#define SCENEOBJECTS_H

#include <list>
#include <initializer_list>
#include <memory>
#include "ObjectVisitor.h"
#include "Coord.h"

using namespace std;

class SceneObject
{
public:
    virtual ~SceneObject()=default;
    virtual bool isVisible() const = 0;
    virtual bool isComposite() const = 0;
    virtual bool isViewer() const = 0;
    virtual void accept(shared_ptr<ObjectVisitor> visitor) = 0;
    virtual list<shared_ptr<SceneObject>>::iterator begin() {return {};};
    virtual list<shared_ptr<SceneObject>>::iterator end() {return {};};
    virtual size_t get_size() const {return 0;};
    virtual void addObject(shared_ptr<SceneObject> &obj) {};
    virtual void removeObject(list<shared_ptr<SceneObject>>::iterator iter) {};
    virtual void move(const Coord3d &transform_data)=0;
    virtual void rotate(const Coord3d &transform_data, const Coord3d &center) =0;
    virtual void scale(const Coord3d &transform_data, const Coord3d &center) =0;
    virtual void rotate(const Coord3d &transform_data) =0;
    virtual void scale(const Coord3d &transform_data) =0;
    virtual Coord3d get_center() = 0;
};

#endif
