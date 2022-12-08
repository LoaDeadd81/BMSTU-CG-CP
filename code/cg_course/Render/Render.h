#ifndef CG_COURSE_RENDER_H
#define CG_COURSE_RENDER_H

#include "Scene.h"
#include "Drawer.h"
#include "Properies.h"

#define EPS 1e-6

class BaseRenderer
{
public:
    BaseRenderer(shared_ptr<BaseDrawer> drawer, RenderProperties &props)
            : drawer(drawer), props(props)
    {};

    shared_ptr<BaseDrawer> &getDrawer()
    { return drawer; };

    RenderProperties &getProps()
    { return props; };

    virtual void render(shared_ptr<Scene> scene) = 0;

protected:
    shared_ptr<BaseDrawer> drawer;
    RenderProperties props;
};

class RayTracingRendered : public BaseRenderer
{
public:
    using BaseRenderer::BaseRenderer;

    RayTracingRendered() = default;

    virtual void render(shared_ptr<Scene> scene) override;

private:
    bool emitRay(const shared_ptr<Scene> &scene, const Ray &r, Color &color, int depth);

    double computeLight(const shared_ptr<Scene> &scene, const Point3d &p, const Vec3d &n, const Vec3d &v,
                        const ObjectProperties &prop);

    static bool closest_intersection(const shared_ptr<Scene> &scene, const Ray &r, IntersectionData &data,
                                     double t_min = EPS,
                                     double t_max = std::numeric_limits<double>::max()
    );

    static double mirror_reflection(const Vec3d &r, const Vec3d &v, double s);

    static Vec3d reflectedRay(const Vec3d &l, const Vec3d &n);

    static Vec3d refractedRay(const Vec3d &l, const Vec3d &n, double mi);

};

#endif
