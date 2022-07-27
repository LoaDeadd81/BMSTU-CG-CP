#ifndef SIMPLEOBJECT_H
#define SIMPLEOBJECT_H

#include "SceneObjects.h"

class SimpleObject : public SceneObject
{
public:
    virtual ~SimpleObject()  override = default;
    virtual bool isComposite() const override {return false;};
};

class VisibleObject : public SimpleObject
{
public:
    virtual ~VisibleObject()  = default;
    virtual bool isVisible() const override {return true;};
    virtual bool isViewer() const override {return false;};
};

class InvisibleObject : public SimpleObject
{
public:
    virtual ~InvisibleObject()  = default;
    virtual bool isVisible() const override {return false;};
};

#endif
