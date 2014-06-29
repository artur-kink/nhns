#ifndef _BASEENTITY_
#define _BASEENTITY_

#include <cmath>
#include "Types.hpp"
#include "BaseObject.hpp"
#include "Content/Map.hpp"

/** 
* Base class for a game entity.
*/
class BaseEntity:public BaseObject{
public:

	BaseEntity();

    virtual void update(unsigned int frameTime) = 0;
};

#endif
