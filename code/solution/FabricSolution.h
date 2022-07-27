#ifndef FABRICSOLUTION_H
#define FABRICSOLUTION_H

#include <map>
#include <string>

#include "FabricCreator.h"

using namespace std;

class FabricSolution
{
public:
    ~FabricSolution() = default;
    void registeraation(string name, shared_ptr<FabricCreator> creator);
    void configure(string name);
    shared_ptr<FabricCreator> get_creator();
private:
    static map<string, shared_ptr<FabricCreator>> map;
    static shared_ptr<FabricCreator> current;
};

#endif
