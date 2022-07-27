#include "Commands.h"


DelObjectCommand::DelObjectCommand(size_t i) : index(i)
{
}

void DelObjectCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<DelObjectManager>(manager)->execute(index);
}

AddObjectCommand::AddObjectCommand(shared_ptr<SceneObject> obj) : object(obj)
{

}

void AddObjectCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<AddObjectManager>(manager)->execute(object);
}

ChangeCameraCommand::ChangeCameraCommand(size_t i) : index(i)
{

}

void ChangeCameraCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<ChangeCameraManager>(manager)->execute(index);
}

LoadObjectCommand::LoadObjectCommand(string filename) : filename(filename)
{

}

void LoadObjectCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<LoadObjectManager>(manager)->execute(filename);
}

LoadCameraCommand::LoadCameraCommand(string filename) : LoadObjectCommand(filename)
{

}

void LoadCameraCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<LoadCameraManager>(manager)->execute(filename);
}


DrawCommand::DrawCommand(shared_ptr<BaseDrawer> drawer) : drawer(drawer)
{

}

void DrawCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<DrawManager>(manager)->execute(drawer);
}

TransformCommand::TransformCommand(size_t i, const Coord3d &data, const Coord3d &center)
        : index(i), data(data), center(center)
{

}

MoveCommand::MoveCommand(size_t i, const Coord3d &data) : TransformCommand(i, data)
{

}

void MoveCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<MoveManager>(manager)->execute(index, data);
}

RotateCommand::RotateCommand(size_t i, const Coord3d &data, const Coord3d &center) : TransformCommand(i, data, center)
{

}

void RotateCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<RotateManager>(manager)->execute(index, data, center);
}

ScaleCommand::ScaleCommand(size_t i, const Coord3d &data, const Coord3d &center) : TransformCommand(i, data, center)
{

}

void ScaleCommand::execute(shared_ptr<BaseManager> manager)
{
    dynamic_pointer_cast<ScaleManager>(manager)->execute(index, data, center);
}


