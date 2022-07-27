#include "Managers.h"

AddObjectManager::AddObjectManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void AddObjectManager::execute(shared_ptr<SceneObject> obj)
{
    scene->add_object(obj);
}

DelObjectManager::DelObjectManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void DelObjectManager::execute(size_t i)
{
    scene->del_object(i);
}

ChangeCameraManager::ChangeCameraManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void ChangeCameraManager::execute(size_t i)
{
    scene->set_cam(i);
}

LoadObjectManager::LoadObjectManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void LoadObjectManager::execute(string &filename)
{
    shared_ptr<BaseBuilder> builder = ModelBuilderSolution().get_creator()->create();
    shared_ptr<BaseLoader> loader = LoaderSolution().get_creator()->create();
    shared_ptr<BaseBuildDirector> director = ModelDirectorSolution().get_creator()->create(builder, loader);
    shared_ptr<SceneObject> object = director->create(filename);
    scene->add_object(object);
}

LoadCameraManager::LoadCameraManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void LoadCameraManager::execute(string &filename)
{
    shared_ptr<BaseBuilder> builder = CameraBuilderCreator().create();
    shared_ptr<BaseLoader> loader = LoaderSolution().get_creator()->create();
    shared_ptr<BaseBuildDirector> director = CameraDirectorCreator().create(builder, loader);
    shared_ptr<SceneObject> object = director->create(filename);
    scene->add_object(object);
}

DrawManager::DrawManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void DrawManager::execute(shared_ptr<BaseDrawer> drawer)
{
    bool cam_exist = false;
    for (auto i = scene->begin(); !cam_exist && i != scene->end(); i++)
        if((*i)->isViewer()) cam_exist = true;
    if (!cam_exist)
    {
        time_t t_time = time(NULL);
        throw CamExistError(__FILE__, __FUNCTION__ , __LINE__, ctime(&t_time), "Can't draw without camera");
    }

    drawer->clear();
    shared_ptr<ObjectVisitor> visitor = DrawVisitorCreator().create(drawer, scene->get_cam());
    for (auto i = scene->begin(); i != scene->end(); i++)
        (*i)->accept(visitor);
}

MoveManager::MoveManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void MoveManager::execute(size_t i, const Coord3d &data)
{
    auto it = scene->begin();
    for (int j = 0; j < i; j++, it++);
    shared_ptr<ObjectVisitor> visitor = MoveVisitorCreator().create(data);
    (*it)->accept(visitor);
}

RotateManager::RotateManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void RotateManager::execute(size_t i, const Coord3d &data, const Coord3d &center)
{
    auto it = scene->begin();
    for (int j = 0; j < i; j++, it++);
    shared_ptr<ObjectVisitor> visitor = RotateVisitorCreator().create(data, center);
    (*it)->accept(visitor);
}

ScaleManager::ScaleManager(shared_ptr<BaseScene> scene) : BaseManager(scene)
{

}

void ScaleManager::execute(size_t i, const Coord3d &data, const Coord3d &center)
{
    auto it = scene->begin();
    for (int j = 0; j < i; j++, it++);
    shared_ptr<ObjectVisitor> visitor = ScaleVisitorCreator().create(data, center);
    (*it)->accept(visitor);
}
