#include "DirectorSolution.h"

map<string, shared_ptr<ModelDirectorCreator>> ModelDirectorSolution::map;
shared_ptr<ModelDirectorCreator> ModelDirectorSolution::current;

void ModelDirectorSolution::registeraation(string name, shared_ptr<ModelDirectorCreator> creator)
{
    map.insert(make_pair(name, creator));
}

void ModelDirectorSolution::configure(string name)
{
    current = map[name];;
}

shared_ptr<ModelDirectorCreator> ModelDirectorSolution::get_creator()
{
    return current;
}
