#include "CommandCreators.h"

shared_ptr<BaseCommand> DelObjectCommandCreator::create(size_t i)
{
    shared_ptr<BaseCommand> com = make_shared<DelObjectCommand>(i);
    return com;
}

shared_ptr<BaseCommand> AddObjectCommandCreator::create(shared_ptr<SceneObject> obj)
{
    shared_ptr<BaseCommand> com = make_shared<AddObjectCommand>(obj);
    return com;
}

shared_ptr<BaseCommand> ChangeCameraCommandCreator::create(size_t i)
{
    shared_ptr<BaseCommand> com = make_shared<ChangeCameraCommand>(i);
    return com;
}

shared_ptr<BaseCommand> LoadObjectCommandCreator::create(string filename)
{
    shared_ptr<BaseCommand> com = make_shared<LoadObjectCommand>(filename);
    return com;
}

shared_ptr<BaseCommand> LoadCameraCommandCreator::create(string filename)
{
    shared_ptr<BaseCommand> com = make_shared<LoadCameraCommand>(filename);
    return com;
}

shared_ptr<BaseCommand>
DrawCommandCreator::create(shared_ptr<BaseDrawer> drawer)
{
    shared_ptr<BaseCommand> com = make_shared<DrawCommand>(drawer);
    return com;
}

shared_ptr<BaseCommand> MoveCommandCreator::create(size_t i, const Coord3d &data)
{
    shared_ptr<BaseCommand> com = make_shared<MoveCommand>(i, data);
    return com;
}

shared_ptr<BaseCommand> RotateCommandCreator::create(size_t i, const Coord3d &data, const Coord3d &center)
{
    shared_ptr<BaseCommand> com = make_shared<RotateCommand>(i, data, center);
    return com;
}

shared_ptr<BaseCommand> ScaleCommandCreator::create(size_t i, const Coord3d &data, const Coord3d &center)
{
    shared_ptr<BaseCommand> com = make_shared<ScaleCommand>(i, data, center);
    return com;
}
