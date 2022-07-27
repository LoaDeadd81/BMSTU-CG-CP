#ifndef OBJECTVISITOR_H
#define OBJECTVISITOR_H


class FrameModelImp;
class Camera;
class CompositeObject;


class ObjectVisitor
{
public:
    virtual ~ObjectVisitor() = default;
    virtual void visit(FrameModelImp &model) = 0;
    virtual void visit(Camera &camera) = 0;
    virtual void visit(CompositeObject &object) = 0;
};

#endif
