#include "FabricCreator.h"

shared_ptr<BaseDrawerFactory> QtFabricCreator::create()
{
    shared_ptr<BaseDrawerFactory> fabric = make_shared<QtDrawerFactory>();
    return fabric;
}
