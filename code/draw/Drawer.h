#ifndef DRAWER_H
#define DRAWER_H

#include "QtDrawTools.h"
#include "DrawTools.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    BaseDrawer(shared_ptr<BaseCanvas> canvas) : canvas(canvas) {};
    virtual ~BaseDrawer() = default;
    virtual void draw_line(double x1, double y1, double x2, double y2) = 0;
    virtual void clear() = 0;

protected:
    shared_ptr<BaseCanvas> canvas;
};

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = default;
    QtDrawer(shared_ptr<BaseCanvas> canvas);
    virtual ~QtDrawer() override = default;
    virtual void draw_line(double x1, double y1, double x2, double y2) override;
    virtual void clear() override;

};

class BaseDrawerFactory
{
public:
    virtual ~BaseDrawerFactory() = default;
    virtual shared_ptr<BaseDrawer> create_drawer(shared_ptr<BaseCanvas> canvas) = 0;
};

class QtDrawerFactory : public BaseDrawerFactory
{
public:
    virtual ~QtDrawerFactory() override = default;
    virtual shared_ptr<BaseDrawer> create_drawer(shared_ptr<BaseCanvas> canvas) override;
};


#endif
