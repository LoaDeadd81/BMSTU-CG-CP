#ifndef DRAWTOOLS_H
#define DRAWTOOLS_H

#include <cstdlib>

class BaseCanvas
{
public:
    virtual ~BaseCanvas() = default;
    virtual void draw_line(double x1, double y1, double x2, double y2) = 0;
    virtual void clear() = 0;
};
#endif
