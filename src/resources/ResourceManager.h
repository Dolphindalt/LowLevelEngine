#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "src/containers/string/CStringTable.h"

class ResourceManager
{
private:

public:
    void *getResourceById(CFixedString &id);
};

#endif