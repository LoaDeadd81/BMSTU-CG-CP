#include "Drawer.h"

QtDrawer::QtDrawer(shared_ptr<QPixmap> pixmap) : painter(pixmap.get()), pen(QPen())
{

}

void QtDrawer::draw_pixel(int x, int y, Color color)
{
    pen.setColor(color);
    painter.setPen(pen);
    painter.drawPoint(x, y);
}

void QtDrawer::clear()
{

}
