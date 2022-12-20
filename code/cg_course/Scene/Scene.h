#ifndef CG_COURSE_SCENE_H
#define CG_COURSE_SCENE_H

#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include <list>

class Scene
{
public:
    using ModelIter = std::list<shared_ptr<BaseModel>>::iterator;
    using LightIter = std::list<shared_ptr<Light>>::iterator;

    Scene() = default;

    Scene(shared_ptr<Camera> &cam);

    ModelIter add(shared_ptr<BaseModel> &model);

    LightIter add(shared_ptr<Light> &light);

    void remove(ModelIter iter);

    void remove(LightIter iter);

    void setColor(ModelIter iter, const Color &color);

    void setColor(LightIter iter, const Color &color);

    ModelIter ModelsBegin();

    ModelIter ModelsEnd();

    LightIter LightsBegin();

    LightIter LightsEnd();

    shared_ptr<Camera> cam();

private:
    std::list<shared_ptr<BaseModel>> model_list;
    std::list<shared_ptr<Light>> light_list;
    shared_ptr<Camera> camera;
};


#endif
