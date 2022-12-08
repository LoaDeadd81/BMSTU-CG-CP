#include "Commands.h"

Matix4x3d getTransMatrix(Vec3d data, TransformType type)
{
    if (type == TransformType::MOVE)
        return getMoveMatrix(data);
    else if (type == TransformType::ROTATE)
        return getRotateMatrix(data);
    else
        return getScaleMatrix(data);
}

AddModelCommand::AddModelCommand(shared_ptr<BaseModel> model) : model(model)
{
}

void AddModelCommand::execute(shared_ptr<Scene> scene)
{
    scene->add(model);
}

AddLightCommand::AddLightCommand(shared_ptr<Light> light) : light(light)
{

}

void AddLightCommand::execute(shared_ptr<Scene> scene)
{
    scene->add(light);
}

DelModelCommand::DelModelCommand(size_t i) : index(i)
{

}

void DelModelCommand::execute(shared_ptr<Scene> scene)
{
    auto it = scene->ModelsBegin();
    scene->remove(it + index);
}

DelLightCommand::DelLightCommand(size_t i) : index(i)
{

}

void DelLightCommand::execute(shared_ptr<Scene> scene)
{
    auto it = scene->LightsBegin();
    scene->remove(it + index);
}

TransformModelCommand::TransformModelCommand(Vec3d data, TransformType type, size_t i) : index(i)
{
    transform_matrix = getTransMatrix(data, type);
}

void TransformModelCommand::execute(shared_ptr<Scene> scene)
{
    auto it = scene->ModelsBegin() + index;
    (*it)->transform(transform_matrix);
}

TransformLightCommand::TransformLightCommand(Vec3d data, TransformType type, size_t i) : index(i)
{
    transform_matrix = getTransMatrix(data, type);
}

void TransformLightCommand::execute(shared_ptr<Scene> scene)
{
    auto it = scene->LightsBegin() + index;
    (*it)->transform(transform_matrix);
}

TransformCameraCommand::TransformCameraCommand(Vec3d data, TransformType type)
{
    transform_matrix = getTransMatrix(data, type);
}

void TransformCameraCommand::execute(shared_ptr<Scene> scene)
{
    scene->Camera()->transform(transform_matrix);
}

RenderCommand::RenderCommand(shared_ptr<BaseRenderer> renderer) : renderer(renderer)
{

}

void RenderCommand::execute(shared_ptr<Scene> scene)
{
    renderer->render(scene);
}

//RenderCommand::RenderCommand(shared_ptr<BaseDrawer> drawer, RenderProperties properties)
//        : drawer(drawer), props(properties)
//{
//
//}

//void RenderCommand::execute(shared_ptr<Scene> scene)
//{
//    int height = props.s_height, width = props.s_width;
//    double aspect_ratio = double(width) / height;
//    double viewport_height = props.v_height;
//    double viewport_width = aspect_ratio * viewport_height;
//    double focal_length = props.f_len;
//
//    Point3d origin = {0, 0, 0};
//    Vec3d horizontal = {viewport_width, 0, 0}, vertical = {0, viewport_height, 0};
//    Point3d lower_left_corner = origin - horizontal / 2 - vertical / 2 - Point3d{0, 0, focal_length};
//
//    Color color{0, 0, 0};
//
//    for (int j = 0; j < height; j++)
//    {
//        for (int i = 0; i < width; i++)
//        {
//            auto u = double(i) / (width - 1);
//            auto v = double(j) / (height - 1);
//            Vec3d dir = lower_left_corner + u * horizontal + v * vertical - origin;
//            dir.norm();
//            Ray r(origin, dir);
//
//            bool flag = emitRay(scene, r, color, props.max_depth);
//
//            if (flag)
//                drawer->draw_pixel(i, height - j, color);
//        }
//    }
//}
//
//bool RenderCommand::emitRay(shared_ptr<Scene> scene, Ray r, Color &color, int depth)
//{
//    IntersectionData data;
//    color = {0, 0, 0};
//
//    bool flag = closest_intersection(scene, r, data);
//
//    if (!flag)
//        return false;
//
//    color = data.color * computeLight(scene, data.p, data.n, -r.direction, (*data.iter)->props());
//
//    if (depth <= 0)
//        return true;
//
//    if((*data.iter)->props().reflective > 0)
//    {
//        Ray refl_ray(data.p, reflectedRay(-r.direction, data.n));
//        Color refl_color;
//        if (emitRay(scene, refl_ray, refl_color, depth - 1))
//            color += (*data.iter)->props().reflective * refl_color;
//    }
//
//    if((*data.iter)->props().refraction > 0)
//    {
//        Ray refr_ray(data.p, refractedRay(-r.direction, data.n, 1.0 / 1.5));
//        Color refr_color;
//        if(emitRay(scene, refr_ray, refr_color, depth - 1))
//            color += (*data.iter)->props().refraction * refr_color;
//    }
//    return true;
//}
//
//bool
//RenderCommand::closest_intersection(shared_ptr<Scene> scene, Ray r, IntersectionData &data, double t_min, double t_max)
//{
//    IntersectionData cur_data;
//    data.t = std::numeric_limits<double>::max();
//    bool flag = false;
//
//    for (auto it = scene->ModelsBegin(); it != scene->ModelsEnd(); it++)
//        if ((*it)->intersect(r, cur_data) && cur_data.t < data.t && cur_data.t > EPS)
//        {
//            flag = true;
//            data = cur_data;
//            data.iter = it;
//        }
//
//    if (flag)
//        return t_min <= data.t && data.t <= t_max;
//
//    return false;
//}
//
//double RenderCommand::computeLight(shared_ptr<Scene> scene, Point3d p, Vec3d n, Vec3d v, ObjectProperties prop)
//{
//    double res = props.ambient;
//
//    IntersectionData data;
//
//    for (auto it = scene->LightsBegin(); it != scene->LightsEnd(); it++)
//    {
//        Vec3d l = (*it)->origin - p;
//
//        //todo баг когда в источник света за объектом (вроде поправил)
//        bool is_light = closest_intersection(scene, {p, l}, data, EPS, 1);
//        if (is_light)
//            continue;
//
//        res += diffuse_reflection(it, l, p, n);
//        res += mirror_reflection(it, l, p, n, v, prop.shine); //todo светится с обратной стороны от источника
//    }
//
//    return res;
//}
//
//double RenderCommand::diffuse_reflection(Scene::LightIter it, Vec3d l, Point3d p, Vec3d n)
//{
//    double n_dot_l = n & l;
//    if (n_dot_l > 0)
//        return (*it)->I * n_dot_l / (n.len() * l.len());
//    return 0;
//}
//
//double RenderCommand::mirror_reflection(Scene::LightIter it, Vec3d l, Point3d p, Vec3d n, Vec3d v, double s)
//{
//    Vec3d r = reflectedRay(l, n);
//
////    double r_dot_v = r & v, n_dot_l = n & l;
////    if (n_dot_l > 0 && r_dot_v > 0)
////        return (*it)->I * pow(r_dot_v / (r.len() * v.len()), s);
////    return 0;
//
//    double r_dot_v = r & v;
//    if (r_dot_v > 0)
//        return (*it)->I * pow(r_dot_v / (r.len() * v.len()), s);
//    return 0;
//
//}
//
//Vec3d RenderCommand::reflectedRay(Vec3d l, Vec3d n)
//{
//    return 2.0 * n * (n & l) - l;
//}
//
//Vec3d RenderCommand::refractedRay(Vec3d l, Vec3d n, double mi)
//{
//    double cos_teta = l & n, n_coef = (mi * cos_teta - std::sqrt(1 - (mi * mi * (1 - cos_teta * cos_teta))));
//    return mi * (-l) + n_coef * n;
//}

