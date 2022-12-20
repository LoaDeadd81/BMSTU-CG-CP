#ifndef CG_COURSE_COMMANDS_H
#define CG_COURSE_COMMANDS_H

#include <thread>

//#include "Vec.h"
//#include "Model.h"
//#include "Light.h"
//#include "Scene.h"
#include "Transformation.h"
//#include "Scene.h"
#include "Render.h"

enum class TransformType
{
    MOVE, ROTATE, SCALE
};

class BaseCommand
{
public:
    BaseCommand() = default;

    virtual ~BaseCommand() = default;

    virtual void execute(shared_ptr<Scene> scene) = 0;
};

class AddCommand : public BaseCommand
{
public:
    AddCommand() = default;

    virtual ~AddCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) = 0;

public:
    Scene::ModelIter m_iter;
    Scene::LightIter l_iter;
};

class AddModelCommand : public AddCommand
{
public:
    AddModelCommand() = default;

    AddModelCommand(shared_ptr<BaseModel> model);

    virtual ~AddModelCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    shared_ptr<BaseModel> model;
};

class AddLightCommand : public AddCommand
{
public:
    AddLightCommand() = default;

    AddLightCommand(shared_ptr<Light> light);

    virtual ~AddLightCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    shared_ptr<Light> light;
};

class DelModelCommand : public BaseCommand
{
public:
    DelModelCommand() = default;

    DelModelCommand(Scene::ModelIter iter);

    virtual ~DelModelCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    Scene::ModelIter iter;
};

class DelLightCommand : public BaseCommand
{
public:
    DelLightCommand() = default;

    DelLightCommand(Scene::LightIter iter);

    virtual ~DelLightCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    Scene::LightIter iter;
};

class TransformModelCommand : public BaseCommand
{
public:
    TransformModelCommand() = default;

    TransformModelCommand(Vec3d &data, TransformType type, Scene::ModelIter iter);

    virtual ~TransformModelCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    Scene::ModelIter iter;
    Vec3d data;
    TransformType type;
};

class TransformLightCommand : public BaseCommand
{
public:
    TransformLightCommand() = default;

    TransformLightCommand(Vec3d &data, TransformType type, Scene::LightIter iter);

    virtual ~TransformLightCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    Scene::LightIter iter;
    Vec3d data;
    TransformType type;
};

class TransformCameraCommand : public BaseCommand
{
public:
    TransformCameraCommand() = default;

    TransformCameraCommand(Vec3d data, TransformType type);

    virtual ~TransformCameraCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    Vec3d data;
    TransformType type;
};

class RenderCommand : public BaseCommand
{
public:
    RenderCommand() = default;

    RenderCommand(shared_ptr<BaseRenderer> renderer, size_t thread_number);

    virtual ~RenderCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    shared_ptr<BaseRenderer> renderer;
    size_t thread_number;
};

//class RenderCommand : public BaseCommand
//{
//public:
//    RenderCommand() = default;
//
//    RenderCommand(shared_ptr<BaseDrawer> drawer, RenderProperties properties);
//
//    virtual ~RenderCommand() override = default;
//
//    virtual void execute(shared_ptr<Scene> scene) override;
//
//private:
//    Vec3d refractedRay(Vec3d l, Vec3d n, double mi);
//
//    Vec3d reflectedRay(Vec3d l, Vec3d n);
//
//    bool emitRay(shared_ptr<Scene> scene, Ray r, Color &color, int depth);
//
//    bool closest_intersection(shared_ptr<Scene> scene, Ray r, IntersectionData &data,
//                              double t_min = EPS,
//                              double t_max = std::numeric_limits<double>::max()
//    );
//
//    double computeLight(shared_ptr<Scene> scene, Point3d p, Vec3d n, Vec3d v, ObjectProperties prop);
//
//    double diffuse_reflection(Scene::LightIter it, Vec3d l, Point3d p, Vec3d n);
//
//    double mirror_reflection(Scene::LightIter it, Vec3d l, Point3d p, Vec3d n, Vec3d v, double s);
//
//private:
//    shared_ptr<BaseDrawer> drawer;
//    RenderProperties props;
//};


#endif
