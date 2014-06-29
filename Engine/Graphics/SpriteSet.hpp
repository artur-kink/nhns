#ifndef _SPRITESET_
#define _SPRITESET_

#include "BaseSprite.hpp"
#include <cstring>

/** 
* A set of sprites.
* A spriteset is used to group sprites that are logically used together into one entity.
* An example of this is a character set.
*/
class SpriteSet{

public:
    unsigned short index;

    /** 
    * The sprites in this set.
    */
    BaseSprite** sprites;

    /** 
    * The number of sprites in this set.
    */
    byte numSprites;

    SpriteSet();
    SpriteSet(byte num);
    ~SpriteSet();
};

#endif
