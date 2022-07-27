#include "BuilderSolution.h"

map<string, shared_ptr<ModelBuilderCreator>> ModelBuilderSolution::map;
shared_ptr<ModelBuilderCreator> ModelBuilderSolution::current;

void ModelBuilderSolution::registeraation(string name, shared_ptr<ModelBuilderCreator> creator)
{
    map.insert(make_pair(name, creator));
}

void ModelBuilderSolution::configure(string name)
{
    current = map[name];;
}

shared_ptr<ModelBuilderCreator> ModelBuilderSolution::get_creator()
{
    return current;
}
