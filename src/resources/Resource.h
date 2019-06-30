#ifndef RESOURCE_H
#define RESOURCE_H

#include "src/containers/string/CStringTable.h"

template <class T>
class Resource
{
private:
    T *resource;
    const char *lookup;

    void incrementRefs();
    void decrementRefs();
public:
    Resource() = delete;
    Resource(const char *objectID, T *object);
    Resource(const Resource &);
    ~Resource();

    int getRefs() const;
    T *getResource() const;
};

#include "src/resources/Resource.cpp"
#endif