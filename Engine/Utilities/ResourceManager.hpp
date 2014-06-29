#ifndef _RESOURCEMANAGER_
#define _RESOURCEMANAGER_

#ifdef _PC_
#include "pugixml.hpp"
#include <iostream>
#include <vector>
#endif

#include "Utilities/FileHandler.hpp"

class ResourceManager{
public:
    virtual void load(const char* path) = 0;

#ifdef _PC_
    virtual void loadRaw(const char* file) = 0;
    virtual void save(const char* file) = 0;
#endif
};

#endif