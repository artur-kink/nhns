#ifndef _OBJECTMANAGER_
#define _OBJECTMANAGER_

#include "BaseObject.hpp"

/**
 * Abstract base class for classes that manage
 * lists of objects.
 */
class ObjectManager{
protected:
    /** The number of objects that can be in the manager. */
    unsigned short size;
public:
    ObjectManager(){
        size = 0;
    }

    unsigned short getSize(){
        return size;
    }
    
    /**
     * Add given object to the manager.
     * @param obj BaseObject to add.
     * @return True if added, false otherwise.
     */
    virtual bool add(BaseObject* obj) = 0;

    /**
     * Remove given object from the manager.
     * @param obj BaseObject to remove.
     * @return True if removed, false otherwise.
     */
    virtual bool remove(BaseObject* obj) = 0;

    /**
     * Update state of all objects in manager.
     */
    virtual void update(unsigned int frameTime) = 0;
};

#endif