#include "Scene.h"

Scene::Scene(shared_ptr<Camera> &cam) : camera(cam)
{

}

Scene::ModelIter Scene::add(shared_ptr<BaseModel> &model)
{
    model_list.push_back(model);
    ModelIter it = model_list.end();
    it--;
    return it;
}

Scene::LightIter Scene::add(shared_ptr<Light> &light)
{
    light_list.push_back(light);
    LightIter it = light_list.end();
    it--;
    return it;
}

void Scene::remove(Scene::ModelIter iter)
{
    model_list.erase(iter);
}

void Scene::remove(Scene::LightIter iter)
{
    light_list.erase(iter);
}

void Scene::setColor(Scene::ModelIter iter, const Color &color)
{
    iter->get()->setColor(color);
}

void Scene::setColor(Scene::LightIter iter, const Color &color)
{
    iter->get()->setColor(color);
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

shared_ptr<Camera> Scene::cam()
{
    return camera;
}
