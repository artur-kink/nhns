#include "BaseObject.hpp"

BaseObject::BaseObject(){
    destroyState = BaseObject::d_Clean;
    index = 0;
}

/**
 * Mark object to be destroyed.
 */
void BaseObject::destroy(){
    destroyState = BaseObject::d_Destroy;
}