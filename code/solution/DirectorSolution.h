#ifndef DIRECTORSOLUTION_H
#define DIRECTORSOLUTION_H

#include <map>
#include <string>

#include "DirectorCreators.h"

using namespace std;

class ModelDirectorSolution
{
public:
    ~ModelDirectorSolution() = default;
    void registeraation(string name, shared_ptr<ModelDirectorCreator> creator);
    void configure(string name);
    shared_ptr<ModelDirectorCreator> get_creator();
private:
    static map<string, shared_ptr<ModelDirectorCreator>> map;
    static shared_ptr<ModelDirectorCreator> current;
};

#endif
