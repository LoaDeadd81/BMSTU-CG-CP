#include "Drawer.h"

QtDrawer::QtDrawer(shared_ptr<QImage> image) : image(image)
{
}

void QtDrawer::draw_pixel(int x, int y, Color &color)
{
    image->setPixelColor(x, y, color);
}

void QtDrawer::clear()
{
    image->fill(QColor(0, 0, 0));
}
