#include "RegionManager.hpp"

RegionManager::RegionManager(){
    size = 255;
    for(int i = 0; i < 255; i++){
        regions[i] = 0;
    }
}

void RegionManager::update(unsigned int frameTime){
    for(int i = 0; i < 255; i++){
        if(regions[i]){
            if(regions[i]->destroyState == BaseObject::d_Delete){
                delete regions[i];
                regions[i] = 0;
                continue;
            }else if(regions[i]->destroyState == BaseObject::d_Destroy){
                regions[i]->destroyState = BaseObject::d_Delete;
            }else{
                //
            }
        }
    }
}

Region* RegionManager::getRegion(const char* name){
    for(int i = 0; i < size; i++){
        if(regions[i] && strcmp(regions[i]->name, name) == 0){
            return regions[i];
        }
    }
    return 0;
}

bool RegionManager::add(BaseObject* region){
    if(!static_cast<Region*>(region))
        return false;
    for(int i = 0; i < size; i++){
        if(!regions[i]){
            regions[i] = (Region*)region;
            region->index = i;
            return true;
        }
    }
    return false;
}

void RegionManager::clear(){
    for(int i = 0; i < size; i++){
        if(regions[i]){
            delete regions[i];
            regions[i] = 0;
        }
    }
}

bool RegionManager::remove(BaseObject* region){
    if(!static_cast<Region*>(region))
        return false;
    for(int i = 0; i < size; i++){
        if(regions[i] == region){
            delete regions[i];
            regions[i] = 0;
            return true;
        }
    }
    return false;
}