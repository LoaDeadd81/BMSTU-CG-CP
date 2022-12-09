#ifndef CG_COURSE_SCENE_H
#define CG_COURSE_SCENE_H

#include "Model.h"
#include "Light.h"
#include "Camera.h"
//#include <vector>

class Scene
{
public:
    using ModelIter = std::vector<shared_ptr<BaseModel>>::iterator;
    using LightIter = std::vector<shared_ptr<Light>>::iterator;

    void add(const shared_ptr<BaseModel> model);

    void add(const shared_ptr<Light> light);

    void remove(ModelIter iter);

    void remove(LightIter iter);

    ModelIter ModelsBegin();

    ModelIter ModelsEnd();

    LightIter LightsBegin();

    LightIter LightsEnd();

    shared_ptr<BaseCamera> Camera();

private:
    std::vector<shared_ptr<BaseModel>> model_list;
    std::vector<shared_ptr<Light>> light_list;
    shared_ptr<BaseCamera> camera;
};


#endif
