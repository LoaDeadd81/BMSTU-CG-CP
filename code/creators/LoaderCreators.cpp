#include "LoaderCreators.h"

shared_ptr<BaseLoader> TXTLoaderCreator::create()
{
    shared_ptr<BaseLoader> loader = make_shared<TXTLoader>();
    return loader;
}
