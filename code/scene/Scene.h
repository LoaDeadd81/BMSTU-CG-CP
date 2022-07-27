#ifndef SCENE_H
#define SCENE_H

#include "BaseScene.h"
#include "Camera.h"
#include "Error.h"

class Scene : public BaseScene
{
public:
    Scene() = default;
    virtual ~Scene() override = default;
    virtual size_t get_size() const override;
    virtual shared_ptr<Camera> get_cam() const override;
    virtual void set_cam(size_t i) override;
    virtual void add_object(shared_ptr<SceneObject> obj) override;
    virtual void del_object(size_t i) override;
    virtual list<shared_ptr<SceneObject>>::iterator begin() override;
    virtual list<shared_ptr<SceneObject>>::iterator end() override;
};

#endif
