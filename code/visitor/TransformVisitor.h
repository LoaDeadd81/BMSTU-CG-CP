#ifndef TRANSFORMVISITOR_H
#define TRANSFORMVISITOR_H

#include "Camera.h"
#include "ObjectVisitor.h"
#include "Coord.h"
#include "Model.h"
#include "CompositeObject.h"

class TranformVisitor : public ObjectVisitor
{
public:
    TranformVisitor() = default;
    TranformVisitor(const Coord3d &data, const Coord3d &center = {0, 0, 0}) : center(center), data(data) {};
    virtual ~TranformVisitor() override = default;
protected:
    Coord3d center, data;
};

class MoveVisitor : public TranformVisitor
{
public:
    MoveVisitor(const Coord3d &data);
    virtual ~MoveVisitor() override = default;
    virtual void visit(FrameModelImp &model) override;
    virtual void visit(Camera &camera) override;
    virtual void visit(CompositeObject &object) override;
};

class RotateVisitor : public TranformVisitor
{
public:
    RotateVisitor(const Coord3d &data, const Coord3d &center = {0, 0, 0});
    virtual ~RotateVisitor() override = default;
    virtual void visit(FrameModelImp &model) override;
    virtual void visit(Camera &camera) override;
    virtual void visit(CompositeObject &object) override;
};

class ScaleVisitor : public TranformVisitor
{
public:
    ScaleVisitor(const Coord3d &data, const Coord3d &center = {0, 0, 0});
    virtual ~ScaleVisitor() override = default;
    virtual void visit(FrameModelImp &model) override;
    virtual void visit(Camera &camera) override;
    virtual void visit(CompositeObject &object) override;
};

#endif
