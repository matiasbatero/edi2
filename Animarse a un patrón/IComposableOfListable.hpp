#ifndef I_COMPOSABLE_OF_LISTABLE
#define I_COMPOSABLE_OF_LISTABLE

#include "IListable.hpp"

class IComposableOfListable
{
    public:

    virtual void add(IListable* component) = 0;
    virtual void remove(IListable* component) = 0;
    virtual IListable* getChild(int key) = 0;
    
    virtual ~IComposableOfListable() = default;
};

#endif
