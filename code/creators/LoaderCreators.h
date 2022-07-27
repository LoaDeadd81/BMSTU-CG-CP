#ifndef LOADERCREATORS_H
#define LOADERCREATORS_H

#include "Loader.h"

class LoaderCreator
{
public:
    virtual ~LoaderCreator() = default;
    virtual shared_ptr<BaseLoader> create() = 0;
};

class TXTLoaderCreator : public LoaderCreator
{
public:
    virtual ~TXTLoaderCreator() override = default;
    virtual shared_ptr<BaseLoader> create() override;
};

#endif
