#include "QtToolCreators.h"

shared_ptr<BaseCanvas> QtCanvasCreator::create(shared_ptr<QGraphicsScene> scene)
{
    shared_ptr<BaseCanvas> canvas = make_shared<QtCanvas>(scene);
    return canvas;
}
