#include "DirectorCreators.h"

shared_ptr<BaseBuildDirector> ModelDirectorCreator::create(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader)
{
    shared_ptr<BaseBuildDirector> director = make_shared<ModelBuildDirector>(builder, loader);
    return director;
}

shared_ptr<BaseBuildDirector> CameraDirectorCreator::create(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader)
{
    shared_ptr<BaseBuildDirector> director = make_shared<CameraBuildDirector>(builder, loader);
    return director;
}
