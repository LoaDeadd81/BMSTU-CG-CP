#ifndef SCENEINTERFACE_H
#define SCENEINTERFACE_H

#include "BaseScene.h"
#include "BaseCommand.h"
#include "BaseManager.h"
#include "Managers.h"
#include <map>

enum CommandType {DEL, ADD, CHANGE_CAM, LOAD_OBJECT, LOAD_CAMERA, DRAW, MOVE, ROTATE, SCALE};

class SceneInterface
{
public:
    SceneInterface() = default;
    explicit SceneInterface(shared_ptr<BaseScene> scene);
    void execute(CommandType id, shared_ptr<BaseCommand> command);
private:
    shared_ptr<BaseScene> scene;
    map<CommandType, shared_ptr<BaseManager>> managers;
};

#endif
