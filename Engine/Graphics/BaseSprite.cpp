#include "BaseSprite.hpp"

BaseSprite::BaseSprite(){
    name = 0;
    transformationCounter = 0;
}

void BaseSprite::apply(BaseTransformation* transformation){
    if(transformationCounter == 16)
        return;

    transformations[transformationCounter] = transformation;
    transformationCounter++;
}

/** 
* Does not delete sprite name.
* Sprite name is deleted by SpriteNameIndex in SpriteManager.
*/
BaseSprite::~BaseSprite(){
    name = 0;
}