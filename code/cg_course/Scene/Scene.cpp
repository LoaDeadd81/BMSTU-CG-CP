#include "Scene.h"

void Scene::add(const shared_ptr<BaseModel> model)
{
    model_list.push_back(model);
}

void Scene::add(const shared_ptr<Light> light)
{
    light_list.push_back(light);
}

void Scene::remove(Scene::ModelIter iter)
{
    model_list.erase(iter);
}

void Scene::remove(Scene::LightIter iter)
{
    light_list.erase(iter);
}

Scene::ModelIter Scene::ModelsBegin()
{
    return model_list.begin();
}

Scene::ModelIter Scene::ModelsEnd()
{
    return model_list.end();
}

Scene::LightIter Scene::LightsBegin()
{
    return light_list.begin();
}

Scene::LightIter Scene::LightsEnd()
{
    return light_list.end();
}

shared_ptr<BaseCamera> Scene::Camera()
{
    return camera;
}
