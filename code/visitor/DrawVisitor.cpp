#include "DrawVisitor.h"

DrawVisitor::DrawVisitor(shared_ptr<BaseDrawer> drawer, shared_ptr<Camera> camera) : drawer(drawer), camera(camera)
{

}

void DrawVisitor::visit(FrameModelImp &model)
{
    vector<Dot> dots = model.getDots();
    for(auto it = model.EdgeBegin(); it != model.EdgeEnd(); it++)
    {
        Coord3d start = get_progection(dots[it->getp1()], *camera), end = get_progection(dots[it->getp2()], *camera);
        drawer->draw_line(start.getX(), start.getY(), end.getX(), end.getY());
    }
}

void DrawVisitor::visit(Camera &camera)
{

}

void DrawVisitor::visit(CompositeObject &object)
{
    shared_ptr<ObjectVisitor> tmp_ptr(dynamic_cast<ObjectVisitor*>(this));
    for (auto i = object.begin(); i != object.end(); i++) object.accept(tmp_ptr);
}

Coord3d DrawVisitor::get_progection(Dot point, Camera &cam)
{
    Coord3d cam_pos = cam.pos.getDot();
    Coord3d move_data(-cam_pos.getX(), -cam_pos.getY(), -cam_pos.getZ()),
    rotate_data(-cam.angles.getX(), -cam.angles.getY(), -cam.angles.getZ());
    point.move(move_data);
    point.rotate(cam_pos, rotate_data);
    return point.getDot();
}
