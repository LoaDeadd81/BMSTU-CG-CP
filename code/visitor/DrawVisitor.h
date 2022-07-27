#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include "ObjectVisitor.h"
#include "Drawer.h"
#include "Camera.h"
#include "Model.h"
#include "CompositeObject.h"

class DrawVisitor : public ObjectVisitor
{
public:
    DrawVisitor() = default;
    DrawVisitor(shared_ptr<BaseDrawer> drawer, shared_ptr<Camera> camera);
    virtual ~DrawVisitor() = default;
    virtual void visit(FrameModelImp &model) override;
    virtual void visit(Camera &camera) override;
    virtual void visit(CompositeObject &object) override;
private:
    shared_ptr<BaseDrawer> drawer;
    shared_ptr<Camera> camera;

    Coord3d get_progection(Dot point, Camera &cam);
};

#endif
