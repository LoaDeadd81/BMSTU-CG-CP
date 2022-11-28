#ifndef CG_COURSE_DRAWER_H
#define CG_COURSE_DRAWER_H

#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QColor>

#include "Vec.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;

    virtual ~BaseDrawer() = default;

    virtual void draw_pixel(int x, int y, Color color) = 0;

    virtual void clear() = 0;
};

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = default;

    QtDrawer(shared_ptr<QPixmap> pixmap);

    virtual ~QtDrawer() override = default;

    virtual void draw_pixel(int x, int y, Color color) override;

    virtual void clear() override;

private:
    QPainter painter;
    QPen pen;
};

#endif
