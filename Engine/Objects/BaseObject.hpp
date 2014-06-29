#ifndef _BASEOBJECT_
#define	_BASEOBJECT_

#include <cstring>
#include "Types.hpp"

/**
 * Base class for objects;
 */
class BaseObject{
protected:
    
public:

    /** Codes for destroy state of an object. */
    enum DestroyState{
        /** Object should not be destroyed. */
        d_Clean = 0,
        /** Object has been marked to be destroyed on next update call.*/
        d_Destroy = 1,
        /** Object has been destroyed and must be deleted on next update call. */
        d_Delete = 2,
    };


    /**
     * Flag marking that this object should be removed from the world
     * in the next few updates. An object cannot be removed from the
     * world instantly since it might be in use by other objects and classes,
     * and must be removed from them before it can be deleted.
     */
    byte destroyState;

    /** The index of this entity in its respective entity list.*/
    unsigned short index;

    BaseObject();

    void destroy();
};

#endif