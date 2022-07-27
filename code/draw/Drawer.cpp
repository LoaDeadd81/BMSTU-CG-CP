#include "Drawer.h"

QtDrawer::QtDrawer(shared_ptr<BaseCanvas> canvas) : BaseDrawer(canvas)
{

}

void QtDrawer::draw_line(double x1, double y1, double x2, double y2)
{
    canvas->draw_line(x1, y1, x2, y2);
}

void QtDrawer::clear()
{
    canvas->clear();
}

shared_ptr<BaseDrawer> QtDrawerFactory::create_drawer(shared_ptr<BaseCanvas> canvas)
{
    shared_ptr<BaseDrawer> drawer = make_shared<QtDrawer>(canvas);
    return drawer;
}
