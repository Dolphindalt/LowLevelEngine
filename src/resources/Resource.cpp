#ifndef RESOURCE_IMPL
#define RESOURCE_IMPL

#include "src/resources/Resource.h"

#include "src/debugging/assertions.h"
#include <unordered_map>

using std::unordered_map;

static unordered_map<const char *, int> referenceTable;

template <class T>
Resource<T>::Resource(const char *objectID, T *object)
: resource(object), lookup(objectID)
{
    if (referenceTable.count(lookup) <= 0)
        referenceTable[lookup] = 0;
    incrementRefs();
}

template <class T>
Resource<T>::Resource(const Resource<T> &cpy)
{
    this->lookup = cpy.lookup;
    this->resource = cpy.resource;
    ASSERT(referenceTable.count(lookup) > 0);
    incrementRefs();
}

template <class T>
Resource<T>::~Resource()
{
    decrementRefs();
}

template <class T>
void Resource<T>::incrementRefs()
{
    ASSERT(referenceTable.count(lookup) > 0);
    referenceTable[lookup]++;
}

template <class T>
void Resource<T>::decrementRefs()
{
    ASSERT(referenceTable.count(lookup) > 0);
    referenceTable[lookup]--;
}

template <class T>
int Resource<T>::getRefs() const
{
    ASSERT(referenceTable.count(lookup) > 0);
    return referenceTable[lookup];
}

#endif