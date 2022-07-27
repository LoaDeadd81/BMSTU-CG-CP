#ifndef BUILDER_H
#define BUILDER_H

#include "SceneObjects.h"
#include "Loader.h"
#include "Model.h"
#include "Camera.h"

class BaseBuilder
{
public:
    virtual ~BaseBuilder() = default;
    virtual shared_ptr<SceneObject> get() = 0;
};


class ModelBuilder : public BaseBuilder
{
public:
    virtual ~ModelBuilder() = default;
    void init();
    void build_dots(vector<Dot> &dots);
    void build_edges(vector<Edge> &edges);
    bool check();
    virtual shared_ptr<SceneObject> get();
private:
    shared_ptr<FrameModelImp> model;
};

class CameraBuilder : public BaseBuilder
{
public:
    virtual ~CameraBuilder() = default;
    void init();
    void build_pos(double x, double y, double z);
    void build_dir(double x, double y, double z);
    virtual shared_ptr<SceneObject> get();
private:
    shared_ptr<Camera> camera;
};

class BaseBuildDirector
{
public:
    virtual ~BaseBuildDirector() = default;
    virtual shared_ptr<SceneObject> create(string filename) = 0;
};

class ModelBuildDirector : public BaseBuildDirector
{
public:
    ModelBuildDirector() = default;
    ModelBuildDirector(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader);
    virtual ~ModelBuildDirector() override = default;
    virtual shared_ptr<SceneObject> create(string filename) override;
private:
    shared_ptr<ModelBuilder> builder;
    shared_ptr<BaseLoader> loader;
};

class CameraBuildDirector : public BaseBuildDirector
{
public:
    CameraBuildDirector() = default;
    CameraBuildDirector(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader);
    virtual ~CameraBuildDirector() override = default;
    virtual shared_ptr<SceneObject> create(string filename) override;
private:
    shared_ptr<CameraBuilder> builder;
    shared_ptr<BaseLoader> loader;
};
#endif
