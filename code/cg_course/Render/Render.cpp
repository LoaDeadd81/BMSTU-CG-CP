#include "Render.h"

void RayTracingRendered::render(shared_ptr<Scene> scene)
{
    int height = props.s_height, width = props.s_width;
    double aspect_ratio = double(width) / height;
    double viewport_height = props.v_height;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = props.f_len;

    Point3d origin = {0, 0, 0};
    Vec3d horizontal = {viewport_width, 0, 0}, vertical = {0, viewport_height, 0};
    Point3d lower_left_corner = origin - horizontal / 2 - vertical / 2 - Point3d{0, 0, focal_length};

    Color color{0, 0, 0};

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            auto u = double(i) / (width - 1);
            auto v = double(j) / (height - 1);
            Vec3d dir = lower_left_corner + u * horizontal + v * vertical - origin;
            dir.norm();
            Ray r(origin, dir);

            bool flag = emitRay(scene, r, color, props.max_depth);

            if (flag)
                drawer->draw_pixel(i, height - j, color);
        }
    }
}

bool RayTracingRendered::emitRay(const shared_ptr<Scene> &scene, const Ray &r, Color &color, int depth)
{
    IntersectionData data;
    color = {0, 0, 0};

    bool flag = closest_intersection(scene, r, data);

    if (!flag)
        return false;

    color = data.color * computeLight(scene, data.p, data.n, -r.direction, (*data.iter)->props());

    if (depth <= 0)
        return true;

    if ((*data.iter)->props().reflective > 0)
    {
        Ray refl_ray(data.p, reflectedRay(-r.direction, data.n));
        Color refl_color;
        if (emitRay(scene, refl_ray, refl_color, depth - 1))
            color += (*data.iter)->props().reflective * refl_color;
    }

    if ((*data.iter)->props().refraction > 0)
    {
        Ray refr_ray(data.p, refractedRay(-r.direction, data.n, 1.0 / 1.5));
        Color refr_color;
        if (emitRay(scene, refr_ray, refr_color, depth - 1))
            color += (*data.iter)->props().refraction * refr_color;
    }
    return true;
}

double
RayTracingRendered::computeLight(const shared_ptr<Scene> &scene, const Point3d &p, const Vec3d &n, const Vec3d &v,
                                 const ObjectProperties &prop)
{
    double res = props.ambient;

    IntersectionData data;

    for (auto it = scene->LightsBegin(); it != scene->LightsEnd(); it++)
    {
        Vec3d l = (*it)->origin - p;

        bool is_light = closest_intersection(scene, {p, l}, data, EPS, 1);
        if (is_light)
            continue;
        l.norm();

        double n_dot_l = n & l;
        if (n_dot_l >= 0)
        {
            Vec3d r = reflectedRay(l, n);
            r.norm();

            res += (*it)->I * n_dot_l * prop.diffuse;
            res += (*it)->I * mirror_reflection(r, v, prop.shine) * prop.specular;
        }
    }

    return res;
}

bool
RayTracingRendered::closest_intersection(const shared_ptr<Scene> &scene, const Ray &r, IntersectionData &data,
                                         double t_min,
                                         double t_max)
{
    IntersectionData cur_data;
    data.t = std::numeric_limits<double>::max();
    bool flag = false;

    for (auto it = scene->ModelsBegin(); it != scene->ModelsEnd(); it++)
        if ((*it)->intersect(r, cur_data) && cur_data.t < data.t && cur_data.t > EPS)
        {
            flag = true;
            data = cur_data;
            data.iter = it;
        }

    if (flag)
        return t_min <= data.t && data.t <= t_max;

    return false;
}

double RayTracingRendered::mirror_reflection(const Vec3d &r, const Vec3d &v, double s)
{
    double r_dot_v = r & v;
    if (r_dot_v > 0)
        pow(r_dot_v, s);
    return 0;

}

Vec3d RayTracingRendered::reflectedRay(const Vec3d &l, const Vec3d &n)
{
    return 2.0 * n * (n & l) - l;
}

Vec3d RayTracingRendered::refractedRay(const Vec3d &l, const Vec3d &n, double mi)
{
    double cos_teta = l & n, n_coef = (mi * cos_teta - std::sqrt(1 - (mi * mi * (1 - cos_teta * cos_teta))));
    return mi * (-l) + n_coef * n;
}

