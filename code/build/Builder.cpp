#include "Builder.h"

void ModelBuilder::init()
{
    model = make_shared<FrameModelImp>();
}

void ModelBuilder::build_dots(vector<Dot> &dots)
{
    model->getDots() = dots;
}

void ModelBuilder::build_edges(vector<Edge> &edges)
{
    model->getEdges() = edges;
}

bool ModelBuilder::check()
{
    int size = model->getDots().size();
    for (auto i = model->EdgeBegin(); i != model->EdgeEnd(); i++)
        if (i->getp1() == i->getp2() || i->getp1() >= size || i->getp2() >= size)
            return false;
    return true;
}

shared_ptr<SceneObject> ModelBuilder::get()
{
    shared_ptr<SceneObject> res = make_shared<FrameModel>(model);
    return res;
}

void CameraBuilder::init()
{
    camera = make_shared<Camera>();
}

void CameraBuilder::build_pos(double x, double y, double z)
{
    Dot pos(x, y, z);
    camera->setPos(pos);
}

void CameraBuilder::build_dir(double x, double y, double z)
{
    Coord3d dir(x, y, z);
    camera->setDir(dir);
}

shared_ptr<SceneObject> CameraBuilder::get()
{
    return camera;
}

ModelBuildDirector::ModelBuildDirector(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader) : loader(loader)
{
    this->builder = dynamic_pointer_cast<ModelBuilder>(builder);
}

shared_ptr<SceneObject> ModelBuildDirector::create(string filename)
{
    loader->open(filename);

    size_t dots_size = loader->get_num();
    vector<Dot> dots(dots_size);

    for (Dot &it: dots)
    {
        int x = loader->get_num();
        int y = loader->get_num();
        int z = loader->get_num();

        Coord3d data(x, y, z);
        it = Dot(data);
    }

    size_t edges_size = loader->get_num();
    std::vector<Edge> edges(edges_size);

    for (Edge &it: edges)
    {
        int first_p_i = loader->get_num();
        int second_p_i = loader->get_num();

        it = Edge(first_p_i, second_p_i);
    }

    loader->close();

    builder->init();
    builder->build_dots(dots);
    builder->build_edges(edges);
    if (!builder->check())
    {
        time_t t_time = time(NULL);
        throw BadModel(__FILE__, __FUNCTION__ , __LINE__, ctime(&t_time), "Bad model data");
    }
    return builder->get();
}

CameraBuildDirector::CameraBuildDirector(shared_ptr<BaseBuilder> builder, shared_ptr<BaseLoader> loader) : loader(loader)
{
    this->builder = dynamic_pointer_cast<CameraBuilder>(builder);
}

shared_ptr<SceneObject> CameraBuildDirector::create(string filename)
{
    loader->open(filename);

    int cam_pos_x = loader->get_num();
    int cam_pos_y = loader->get_num();
    int cam_pos_z = loader->get_num();

    int cam_angle_x = loader->get_num();
    int cam_angle_y = loader->get_num();
    int cam_angle_z = loader->get_num();

    loader->close();

    builder->init();
    builder->build_pos(cam_pos_x, cam_pos_y, cam_pos_z);
    builder->build_dir(cam_angle_x, cam_angle_y, cam_angle_z);

    return  builder->get();
}




