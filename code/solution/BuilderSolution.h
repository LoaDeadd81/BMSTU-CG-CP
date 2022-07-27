#ifndef BUILDERSOLUTION_H
#define BUILDERSOLUTION_H

#include <map>
#include <string>

#include "BuilderCreators.h"

using namespace std;

class ModelBuilderSolution
{
public:
    ~ModelBuilderSolution() = default;
    void registeraation(string name, shared_ptr<ModelBuilderCreator> creator);
    void configure(string name);
    shared_ptr<ModelBuilderCreator> get_creator();
private:
    static map<string, shared_ptr<ModelBuilderCreator>> map;
    static shared_ptr<ModelBuilderCreator> current;
};

#endif
