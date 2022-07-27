#include "QtDrawTools.h"

QtCanvas::QtCanvas(shared_ptr<QGraphicsScene> scene) : scene(scene)
{

}

QtCanvas::QtCanvas(const QtCanvas &canvas)
{
    scene = canvas.scene;
}

void QtCanvas::draw_line(double x1, double y1, double x2, double y2)
{
    scene->addLine(x1, y1, x2, y2);
}

void QtCanvas::clear()
{
    scene->clear();
}

