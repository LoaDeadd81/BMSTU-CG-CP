#include "SceneInterface.h"

SceneInterface::SceneInterface(shared_ptr<BaseScene> scene) : scene(scene)
{
    managers.insert(make_pair(DEL, make_shared<DelObjectManager>(scene)));
    managers.insert(make_pair(ADD, make_shared<AddObjectManager>(scene)));
    managers.insert(make_pair(CHANGE_CAM, make_shared<ChangeCameraManager>(scene)));
    managers.insert(make_pair(LOAD_OBJECT, make_shared<LoadObjectManager>(scene)));
    managers.insert(make_pair(LOAD_CAMERA, make_shared<LoadCameraManager>(scene)));
    managers.insert(make_pair(DRAW, make_shared<DrawManager>(scene)));
    managers.insert(make_pair(MOVE, make_shared<MoveManager>(scene)));
    managers.insert(make_pair(ROTATE, make_shared<RotateManager>(scene)));
    managers.insert(make_pair(SCALE, make_shared<ScaleManager>(scene)));
}

void SceneInterface::execute(CommandType id, shared_ptr<BaseCommand> command)
{
    command->execute(managers[id]);
}
