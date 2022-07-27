#include "VisitorCreators.h"

shared_ptr<ObjectVisitor> MoveVisitorCreator::create(const Coord3d &data)
{
    shared_ptr<ObjectVisitor> visitor = make_shared<MoveVisitor>(data);
    return visitor;
}

shared_ptr<ObjectVisitor> RotateVisitorCreator::create(const Coord3d &data, const Coord3d &center)
{
    shared_ptr<ObjectVisitor> visitor = make_shared<RotateVisitor>(data, center);
    return visitor;
}

shared_ptr<ObjectVisitor> ScaleVisitorCreator::create(const Coord3d &data, const Coord3d &center)
{
    shared_ptr<ObjectVisitor> visitor = make_shared<ScaleVisitor>(data, center);
    return visitor;
}

shared_ptr<ObjectVisitor> DrawVisitorCreator::create(shared_ptr<BaseDrawer> drawer, shared_ptr<Camera> camera)
{
    shared_ptr<ObjectVisitor> visitor = make_shared<DrawVisitor>(drawer, camera);
    return visitor;
}
