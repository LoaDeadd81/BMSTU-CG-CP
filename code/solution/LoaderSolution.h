#ifndef LOADERSOLUTION_H
#define LOADERSOLUTION_H

#include <map>
#include <string>

#include "LoaderCreators.h"

using namespace std;

class LoaderSolution
{
public:
    ~LoaderSolution() = default;
    void registeraation(string name, shared_ptr<LoaderCreator> creator);
    void configure(string name);
    shared_ptr<LoaderCreator> get_creator();
private:
    static map<string, shared_ptr<LoaderCreator>> map;
    static shared_ptr<LoaderCreator> current;
};

#endif
