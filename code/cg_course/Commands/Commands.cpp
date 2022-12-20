#include "Commands.h"

void transform(Vec3d &data, TransformType type, Scene::ModelIter iter)
{
    if (type == TransformType::MOVE)
        iter->get()->move(data[0], data[1], data[2]);
    else if (type == TransformType::ROTATE)
        iter->get()->rotate(data[0], data[1], data[2]);
    else
        iter->get()->scale(data[0], data[1], data[2]);
}

void transform(Vec3d &data, TransformType type, Scene::LightIter iter)
{
    if (type == TransformType::MOVE)
        iter->get()->move(data[0], data[1], data[2]);
}

void transform(Vec3d &data, TransformType type, shared_ptr<Camera> cam)
{
    if (type == TransformType::MOVE)
        cam->move(data[0], data[1], data[2]);
    else if (type == TransformType::ROTATE)
        cam->rotate(data[0], data[1], data[2]);
}

AddModelCommand::AddModelCommand(shared_ptr<BaseModel> model) : model(model)
{
}

void AddModelCommand::execute(shared_ptr<Scene> scene)
{
    m_iter = scene->add(model);
}

AddLightCommand::AddLightCommand(shared_ptr<Light> light) : light(light)
{

}

void AddLightCommand::execute(shared_ptr<Scene> scene)
{
    l_iter = scene->add(light);
}

DelModelCommand::DelModelCommand(Scene::ModelIter iter) : iter(iter)
{

}

void DelModelCommand::execute(shared_ptr<Scene> scene)
{
    scene->remove(iter);
}

DelLightCommand::DelLightCommand(Scene::LightIter iter) : iter(iter)
{

}

void DelLightCommand::execute(shared_ptr<Scene> scene)
{
    scene->remove(iter);
}

TransformModelCommand::TransformModelCommand(Vec3d &data, TransformType type, Scene::ModelIter iter)
        : iter(iter), data(data), type(type)
{
}

void TransformModelCommand::execute(shared_ptr<Scene> scene)
{
    transform(data, type, iter);
}

TransformLightCommand::TransformLightCommand(Vec3d &data, TransformType type, Scene::LightIter iter)
        : iter(iter), data(data), type(type)
{
}

void TransformLightCommand::execute(shared_ptr<Scene> scene)
{
    transform(data, type, iter);
}

TransformCameraCommand::TransformCameraCommand(Vec3d data, TransformType type)
        : data(data), type(type)
{
}

void TransformCameraCommand::execute(shared_ptr<Scene> scene)
{
    transform(data, type, scene->cam());
}

RenderCommand::RenderCommand(shared_ptr<BaseRenderer> renderer, size_t thread_number)
        : renderer(renderer), thread_number(thread_number)
{

}

void run_thread(shared_ptr<BaseRenderer> renderer, shared_ptr<Scene> scene, int min_x, int max_x)
{
    renderer->render(scene, min_x, max_x);
}

void RenderCommand::execute(shared_ptr<Scene> scene)
{
    std::vector<std::thread> threads;
    int w_step = renderer->width() / thread_number, cur_x = 0;
    for (int i = 0; i < thread_number; i++)
    {
        threads.emplace_back(run_thread, renderer, scene, cur_x, cur_x + w_step);
        cur_x += w_step;
    }

    for (auto &th: threads)
        th.join();
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
//        bool is_light = closest_intersection(scene, {p, l}, data, EPS, 1);
//        if (is_light)
//            continue;
//
//        res += diffuse_reflection(it, l, p, n);
//        res += mirror_reflection(it, l, p, n, v, prop.shine)
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

