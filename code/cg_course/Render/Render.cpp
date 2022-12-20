#include "Render.h"

void RayTracingRendered::render(shared_ptr<Scene> scene, int min_x, int max_x)
{
    int height = props.s_height, width = props.s_width;
    double aspect_ratio = double(width) / height;
    double viewport_height = props.v_height;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = props.f_len;

    Point3d origin = scene->cam()->origin;
    Vec3d right = scene->cam()->dir ^ scene->cam()->up;
    Vec3d dir_f = scene->cam()->dir * focal_length,
            v_2 = scene->cam()->up * (viewport_height / 2.0),
            h_2 = right * (viewport_width / 2.0);
    Point3d lb_corner = origin + dir_f - v_2 - h_2,
            rb_corner = origin + dir_f - v_2 + h_2,
            lt_corner = origin + dir_f + v_2 - h_2;
    Vec3d horizontal = rb_corner - lb_corner, vertical = lt_corner - lb_corner;

    Color color{0, 0, 0};
    double du = 1.0 / (width - 1), dv = 1.0 / (height - 1);
    double min_u = double(min_x) / (width - 1), cu = min_u, cv = dv;
    for (int j = 1; j < height; j++)
    {
        for (int i = min_x; i < max_x; i++)
        {
            color = {0, 0, 0};
            auto u = double(i) / (width - 1);
            auto v = double(j) / (height - 1);
            Vec3d dir = lb_corner + u * horizontal + v * vertical - origin;
            dir.norm();
            Ray r(origin, dir);

            if (emitRay(scene, r, color, props.max_depth))
                drawer->draw_pixel(i, height - j, color);

            cu += du;
        }
        cu = min_u;
        cv += dv;
    }
}

bool RayTracingRendered::emitRay(const shared_ptr<Scene> &scene, const Ray &r, Color &color, int depth)
{
    IntersectionData data, tmp_data;

    if (!closest_intersection(scene, r, data))
        return false;
    Color ambient, diffuse, specular, reflect, refract;
    color = {0, 0, 0};

    ambient = props.ambient * data.color;


    for (auto it = scene->LightsBegin(); it != scene->LightsEnd(); it++)
    {
        Vec3d l = (*it)->origin - data.p;

        if (closest_intersection(scene, {data.p, l}, tmp_data, EPS, 1))
            continue;
        l.norm();

        double n_dot_l = data.n & l;
        if (n_dot_l >= 0)
        {
            Vec3d refl = reflectedRay(-l, data.n);
            refl.norm();

            if ((*data.iter)->props().diffuse > 0)
                diffuse += (*it)->comp_color * n_dot_l * (*data.iter)->props().diffuse;
            if ((*data.iter)->props().specular > 0)
                specular += (*it)->comp_color * mirror_reflection(refl, -r.direction, (*data.iter)->props().shine) *
                            (*data.iter)->props().specular;
        }
    }

    diffuse.member_mult(data.color);

    if (depth <= 0)
        return true;

    if ((*data.iter)->props().reflective > 0)
    {
        Ray refl_ray(data.p, reflectedRay(r.direction, data.n));
        Color refl_color;
        if (emitRay(scene, refl_ray, refl_color, depth - 1))
            reflect = (*data.iter)->props().reflective * refl_color;
    }

    if ((*data.iter)->props().refraction > 0)
    {
        Ray refr_ray(data.p, refractedRay(r.direction, data.n, props.mi_world / data.iter->get()->props().mi));
        Color refr_color;
        if (emitRay(scene, refr_ray, refr_color, depth - 1))
            refract = (*data.iter)->props().refraction * refr_color;
    }

    color = ambient + diffuse + specular + reflect + refract;

    return true;
}

bool
RayTracingRendered::closest_intersection(const shared_ptr<Scene> &scene, const Ray &r, IntersectionData &data,
                                         double t_min,
                                         double t_max)
{
    IntersectionData cur_data;
    data.t = t_max;
    bool flag = false;

    for (auto it = scene->ModelsBegin(); it != scene->ModelsEnd(); it++)
        if ((*it)->intersect(r, cur_data) && cur_data.t < data.t && cur_data.t > t_min)
        {
            flag = true;
            data = std::move(cur_data);
            data.iter = it;
        }


    return flag;
}

double RayTracingRendered::mirror_reflection(const Vec3d &r, const Vec3d &s, double s_degree)
{
    double r_dot_s = r & s;
    if (r_dot_s > 0)
        return pow(r_dot_s, s_degree);
    return 0;

}

Vec3d RayTracingRendered::reflectedRay(const Vec3d &in, const Vec3d &n)
{
    return in - 2.0 * (in & n) * n;
}

Vec3d RayTracingRendered::refractedRay(const Vec3d &v, const Vec3d &n, double mi)
{
    double cos_teta = (-v) & n, n_coef = (mi * cos_teta - std::sqrt(1 - (mi * mi * (1 - cos_teta * cos_teta))));
    return mi * v + n_coef * n;
}

