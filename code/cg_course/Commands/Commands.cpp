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

AddLightCommand::AddLightCommand(shared_ptr<BaseLight> light) : light(light)
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

RenderCommand::RenderCommand(shared_ptr<BaseDrawer> drawer, CameraProperties properties)
        : drawer(drawer), props(properties)
{

}

void RenderCommand::execute(shared_ptr<Scene> scene)
{
    int height = props.s_height, width = props.s_width;
    double aspect_ratio = double(width) / height;
    double viewport_height = props.v_height;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = props.f_len;

    Point3d origin = {0, 0, 0};
    Vec3d horizontal = {viewport_width, 0, 0}, vertical = {0, viewport_height, 0};
    IntersectionData data;

    Point3d lower_left_corner = origin - horizontal / 2 - vertical / 2 - Point3d{0, 0, focal_length};

    double min_t = std::numeric_limits<double>::max();
    Color color{0, 0, 0};
    bool flag = false;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            auto u = double(i) / (width - 1);
            auto v = double(j) / (height - 1);
            Vec3d dir = lower_left_corner + u * horizontal + v * vertical - origin;
            dir.norm();
            Ray r(origin, dir);

            for (auto it = scene->ModelsBegin(); it != scene->ModelsEnd(); it++)
            {
                if ((*it)->intersect(r, data) && data.t < min_t)
                {
                    min_t = data.t;
                    color = data.color;
                    flag = true;
                }
            }
            if (flag)
                drawer->draw_pixel(i, j, color);
            flag = false;
            min_t = std::numeric_limits<double>::max();
        }
    }
}
