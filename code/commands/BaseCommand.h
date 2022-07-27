#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "BaseScene.h"
#include "BaseManager.h"

class BaseCommand
{
public:
    virtual ~BaseCommand() = default;
    virtual void execute(shared_ptr<BaseManager> manager) = 0;
};

#endif
