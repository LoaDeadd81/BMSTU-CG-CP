#ifndef CG_COURSE_SCENEMANAGER_H
#define CG_COURSE_SCENEMANAGER_H

#include "Scene.h"
#include "Commands.h"

class SceneManager
{
public:
    SceneManager()
    { scene = make_shared<Scene>(); };

    SceneManager(shared_ptr<Camera> &cam)
    {
        scene = make_shared<Scene>(cam);
    };

    void execute(shared_ptr<BaseCommand> command)
    { command->execute(scene); };

    shared_ptr<Scene> getScene()
    { return scene; };
private:
    shared_ptr<Scene> scene;
};

#endif
