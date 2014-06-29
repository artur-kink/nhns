#ifndef _REGIONMANAGER_
#define _REGIONMANAGER_

#include "ObjectManager.hpp"
#include "Region.hpp"

class RegionManager:public ObjectManager{
public:
    Region* regions[255];

    RegionManager();
    
    virtual void update(unsigned int frameTime);
    
    virtual bool add(BaseObject* region);
    virtual bool remove(BaseObject* region);
    virtual void clear();
    virtual Region* getRegion(const char* name);
};

#endif