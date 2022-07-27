#include "FabricSolution.h"

map<string, shared_ptr<FabricCreator>> FabricSolution::map;
shared_ptr<FabricCreator> FabricSolution::current;

void FabricSolution::registeraation(string name, shared_ptr<FabricCreator> creator)
{
    map.insert(make_pair(name, creator));
}

void FabricSolution::configure(string name)
{
    current = map[name];
}

shared_ptr<FabricCreator> FabricSolution::get_creator()
{
    return current;
}
