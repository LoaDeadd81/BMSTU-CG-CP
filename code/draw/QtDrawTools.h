#ifndef QTDRAWTOOLS_H
#define QTDRAWTOOLS_H

#include "DrawTools.h"
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QColor>

using namespace std;

class QtCanvas : public BaseCanvas
{
public:
    QtCanvas() = default;
    QtCanvas(shared_ptr<QGraphicsScene> scene);
    QtCanvas(const QtCanvas &canvas);
    virtual ~QtCanvas() override = default;
    virtual void draw_line(double x1, double y1, double x2, double y2) override;
    virtual void clear() override;
private:
    shared_ptr<QGraphicsScene> scene;
};


#endif
