#include "LayeredSprite.hpp"

/** 
* Create layered sprite with expected layer count and sprite index. 
* @param count Number of layers to allocate.
* @param spriteIndex Index of the sprite.
*/
LayeredSprite::LayeredSprite(byte count,  unsigned short spriteIndex){
    type = BaseSprite::st_Layered;
    layerCount = count;
    index = spriteIndex;
    layers = new BaseSprite*[count];
    memset(layers, 0, sizeof(BaseSprite*)*count);
    name = 0;
}

/** 
* Updates the layered sprite. This is necessary since the layered sprite
* might contain dynamic sprites within it. Nothing in the current sprite
* is modified. Update calls are made to all dynamic layers.
*/
void LayeredSprite::update(int currentTime){
    for(int i = 0; i < layerCount; i++){
        //Check if layer is dynamic.
        DynamicSprite* sprite = dynamic_cast<DynamicSprite*>(layers[i]);
        if(sprite != 0){
            sprite->update(currentTime);
        }
    }
}

void LayeredSprite::draw(BaseRenderTarget* target, RenderObject& obj) const{
    
    for(byte i = 0; i < layerCount; i++){
        RenderObject copyObj;
        copyObj = obj;

        for(byte t = 0; t < transformationCounter; t++)
            transformations[t]->apply(copyObj);
        layers[i]->draw(target, copyObj);
    }
}

#ifdef _PC_
void LayeredSprite::serialize(std::ofstream& destination){
    unsigned char type = 2;
    destination.write((char*) &type, sizeof(type));
    destination.write((char*) &layerCount, sizeof(layerCount));
    for(int l = 0; l < layerCount; l++){
        destination.write((char*) &layers[l]->index, sizeof(layers[l]->index));
    }
}
#endif

void LayeredSprite::deserialize(MemoryPool* source){
    
}

/** 
* Deletes layers from memory. No sprites are deleted.
*/
LayeredSprite::~LayeredSprite(){
    if(layerCount != 0){
        for(int i = 0; i < layerCount; i++){
            layers[i] = 0;
        }
        delete layers;
        layers = 0;
    }
}