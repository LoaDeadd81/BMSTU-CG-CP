#include "Scene.h"

size_t Scene::get_size() const
{
    return objects.size();
}

shared_ptr<Camera> Scene::get_cam() const
{
    return dynamic_pointer_cast<Camera>(*cur_camera);
}

void Scene::set_cam(size_t i)
{
    if(i >= get_size())
    {
        time_t t_time = time(NULL);
        throw RangeError(__FILE__, __FUNCTION__ , __LINE__, ctime(&t_time), "No camera with such index(index out of range)");
    }
    auto it = objects.begin();
    for (size_t j = 0; j < i; j++, it++);
    if(!(*it)->isViewer())
    {
        time_t t_time = time(NULL);
        throw RangeError(__FILE__, __FUNCTION__ , __LINE__, ctime(&t_time), "No cam with such index");
    }
    cur_camera = it;
}

void Scene::add_object(shared_ptr<SceneObject> obj)
{
    objects.push_back(obj);
}

void Scene::del_object(size_t i)
{
    if(i >= get_size())
    {
        time_t t_time = time(NULL);
        throw RangeError(__FILE__, __FUNCTION__ , __LINE__, ctime(&t_time), "No object with such index(index out of range)");
    }
    auto it = objects.begin();
    for (size_t j = 0; j < i; j++, it++);
    objects.erase(it);
}

list<shared_ptr<SceneObject>>::iterator Scene::begin()
{
    return objects.begin();
}

list<shared_ptr<SceneObject>>::iterator Scene::end()
{
    return objects.end();
}
