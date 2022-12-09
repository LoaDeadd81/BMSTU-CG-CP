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

class AddModelCommand : public BaseCommand
{
public:
    AddModelCommand() = default;

    AddModelCommand(shared_ptr<BaseModel> model);

    virtual ~AddModelCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    shared_ptr<BaseModel> model;
};

class AddLightCommand : public BaseCommand
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

    DelModelCommand(size_t i);

    virtual ~DelModelCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    size_t index;
};

class DelLightCommand : public BaseCommand
{
public:
    DelLightCommand() = default;

    DelLightCommand(size_t i);

    virtual ~DelLightCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    size_t index;
};

class TransformModelCommand : public BaseCommand
{
public:
    TransformModelCommand() = default;

    TransformModelCommand(Vec3d data, TransformType type, size_t i = 0);

    virtual ~TransformModelCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    size_t index;
    Matix4x3d transform_matrix;
};

class TransformLightCommand : public BaseCommand
{
public:
    TransformLightCommand() = default;

    TransformLightCommand(Vec3d data, TransformType type, size_t i = 0);

    virtual ~TransformLightCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    size_t index;
    Matix4x3d transform_matrix;
};

class TransformCameraCommand : public BaseCommand
{
public:
    TransformCameraCommand() = default;

    TransformCameraCommand(Vec3d data, TransformType type);

    virtual ~TransformCameraCommand() override = default;

    virtual void execute(shared_ptr<Scene> scene) override;

private:
    size_t index;
    Matix4x3d transform_matrix;
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
