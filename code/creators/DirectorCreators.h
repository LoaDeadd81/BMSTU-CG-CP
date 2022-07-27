#ifndef DIRECTORCREATORS_H
#define DIRECTORCREATORS_H

#include "Builder.h"

class DirectorCreator
{
public:
    virtual ~DirectorCreator() = default;
    virtual shared_ptr<BaseBuildDirector> create(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader) = 0;
};

class ModelDirectorCreator : public DirectorCreator
{
public:
    virtual ~ModelDirectorCreator() override = default;
    virtual shared_ptr<BaseBuildDirector> create(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader) override;
};

class CameraDirectorCreator : public DirectorCreator
{
public:
    virtual ~CameraDirectorCreator() override = default;
    virtual shared_ptr<BaseBuildDirector> create(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader) override;
};

#endif
