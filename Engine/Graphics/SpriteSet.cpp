#include "SpriteSet.hpp"
#include <cstring>

/** 
* Create an empty sprite set.
*/
SpriteSet::SpriteSet(){
    sprites = 0;
    numSprites = 0;
}

/** 
* Create an empty sprite set that can store num sprites.
* @param num The number of sprites that this set can store.
*/
SpriteSet::SpriteSet(byte num){
    numSprites = num;
    sprites = new BaseSprite*[num];
    memset(sprites, 0, num*(sizeof(BaseSprite*)));
}

/** 
* Clears the sprite set.
* Note this does not actually delete the sprites.
* Sprites must be deleted by the SpriteManager.
*/
SpriteSet::~SpriteSet(){
     if(sprites){
         delete sprites;
         sprites = 0;
         numSprites = 0;
     }
 }
