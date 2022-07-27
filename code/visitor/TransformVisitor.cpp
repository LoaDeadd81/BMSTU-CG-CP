#include "TransformVisitor.h"

MoveVisitor::MoveVisitor(const Coord3d &data) : TranformVisitor(data)
{

}

void MoveVisitor::visit(FrameModelImp &model)
{
    model.move(data);
}

void MoveVisitor::visit(Camera &camera)
{
    camera.move(data);
}

void MoveVisitor::visit(CompositeObject &object)
{
    object.move(data);
}

RotateVisitor::RotateVisitor(const Coord3d &data, const Coord3d &center) : TranformVisitor(data, center)
{

}

void RotateVisitor::visit(FrameModelImp &model)
{
    model.rotate(data, center);
}

void RotateVisitor::visit(Camera &camera)
{
    camera.rotate(data);
}

void RotateVisitor::visit(CompositeObject &object)
{
    object.rotate(data, center);
}

ScaleVisitor::ScaleVisitor(const Coord3d &data, const Coord3d &center) : TranformVisitor(data, center)
{

}

void ScaleVisitor::visit(FrameModelImp &model)
{
    model.scale(data, center);
}

void ScaleVisitor::visit(Camera &camera)
{
}

void ScaleVisitor::visit(CompositeObject &object)
{
    object.scale(data, center);
}



