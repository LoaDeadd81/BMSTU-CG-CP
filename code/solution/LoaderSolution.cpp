#include "LoaderSolution.h"

map<string, shared_ptr<LoaderCreator>> LoaderSolution::map;
shared_ptr<LoaderCreator> LoaderSolution::current;

void LoaderSolution::registeraation(string name, shared_ptr<LoaderCreator> creator)
{
    map.insert(make_pair(name, creator));
}

void LoaderSolution::configure(string name)
{
    current = map[name];;
}

shared_ptr<LoaderCreator> LoaderSolution::get_creator()
{
    return current;
}
