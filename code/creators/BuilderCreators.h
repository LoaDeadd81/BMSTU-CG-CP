#ifndef BUILDERCREATORS_H
#define BUILDERCREATORS_H

#include "Builder.h"

class BuilderCreator
{
public:
    virtual ~BuilderCreator() = default;
    virtual shared_ptr<BaseBuilder> create() = 0;
};

class ModelBuilderCreator : public BuilderCreator
{
public:
    virtual ~ModelBuilderCreator() override = default;
    virtual shared_ptr<BaseBuilder> create() override;
};

class CameraBuilderCreator : public BuilderCreator
{
public:
    virtual ~CameraBuilderCreator() override = default;
    virtual shared_ptr<BaseBuilder> create() override;
};

#endif
