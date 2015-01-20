#include "EntityManager.hpp"

EntityManager::EntityManager(){
    //Hardcode a entity size for now.
    size = 255;
    for(int i = 0; i < size; i++){
        entities[i] = 0;
    }
}

/**
 * Update states of entities in entity manager.
 * @param frameTime Time of update.
 */
void EntityManager::update(){
    for(int i = 0; i < size; i++){
        if(entities[i]){
            if(entities[i]->destroyState & BaseObject::d_Delete){
                //Clear from memory of entity is ready to be deleted.
                delete entities[i];
                entities[i] = 0;
                continue;
            }else if(entities[i]->destroyState & BaseObject::d_Destroy){
                //Mark to delete on next update.
                entities[i]->destroyState = BaseObject::d_Delete;
                continue;
            }else{
                entities[i]->update();
            }
        }
    }
}

/**
 * Add an entity to the manager.
 * @param entity Entity to add.
 * @return true if added, false otherwise.
 */
bool EntityManager::add(BaseObject* entity){
    if(!static_cast<BaseEntity*>(entity))
        return false;
    for(int i = 0; i < size; i++){
        if(!entities[i]){
            entities[i] = (BaseEntity*)entity;
            entity->index = i;
            return true;
        }
    }
    return false;
}

/**
 * Remove entity from manager if found.
 * @param entity Entity to remvoe.
 * @return True if removed, else false.
 */
bool EntityManager::remove(BaseObject* entity){
    if(!static_cast<BaseEntity*>(entity))
        return false;
    for(int i = 0; i < size; i++){
        if(entities[i] == entity){
            delete entities[i];
            entities[i] = 0;
            return true;
        }
    }
    return false;
}