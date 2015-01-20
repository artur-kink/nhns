#ifndef _ENTITYMANAGER_
#define _ENTITYMANAGER_

#include "ObjectManager.hpp"
#include "BaseEntity.hpp"

class EntityManager:public ObjectManager{
private:
public:
    BaseEntity* entities[255];

    EntityManager();

    virtual void update();
    virtual bool add(BaseObject* entity);
    virtual bool remove(BaseObject* entity);
};

#endif