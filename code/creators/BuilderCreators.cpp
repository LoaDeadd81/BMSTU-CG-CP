#include "BuilderCreators.h"

shared_ptr<BaseBuilder> ModelBuilderCreator::create()
{
    shared_ptr<BaseBuilder> builder = make_shared<ModelBuilder>();
    return builder;
}

shared_ptr<BaseBuilder> CameraBuilderCreator::create()
{
    shared_ptr<BaseBuilder> builder = make_shared<CameraBuilder>();
    return builder;
}
