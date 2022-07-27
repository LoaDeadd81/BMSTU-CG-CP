#ifndef QTTOOLCREATORS_H
#define QTTOOLCREATORS_H

#include "QtDrawTools.h"

class QtCanvasCreator
{
public:
    shared_ptr<BaseCanvas> create(shared_ptr<QGraphicsScene> scene);
};

#endif
