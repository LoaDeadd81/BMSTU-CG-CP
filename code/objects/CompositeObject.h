#ifndef COMPOSITEOBJEXT_H
#define COMPOSITEOBJEXT_H

#include "SceneObjects.h"

class CompositeObject : public SceneObject
{
public:
    CompositeObject() = default;
    virtual ~CompositeObject() override = default;

    virtual bool isVisible() const override;
    virtual bool isComposite() const override;
    virtual bool isViewer() const override;
    virtual void accept(shared_ptr<ObjectVisitor> visitor) override;

    virtual list<shared_ptr<SceneObject>>::iterator begin() override;
    virtual list<shared_ptr<SceneObject>>::iterator end() override;
    virtual size_t get_size() const override;
    virtual void addObject(shared_ptr<SceneObject> &obj) override;
    virtual void removeObject(list<shared_ptr<SceneObject>>::iterator iter) override;
    virtual void move(const Coord3d &transform_data) override;
    virtual void rotate(const Coord3d &transform_data, const Coord3d &center) override;
    virtual void scale(const Coord3d &transform_data, const Coord3d &center) override;
    virtual void rotate(const Coord3d &transform_data) override;
    virtual void scale(const Coord3d &transform_data) override;
    virtual Coord3d get_center() override;
private:
    list<shared_ptr<SceneObject>> objects;
};

#endif
