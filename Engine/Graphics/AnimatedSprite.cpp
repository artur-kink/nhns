#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(){
    type = BaseSprite::st_Animated;
    frameCount = 0;
    currentFrame = 0;
    lastUpdate = 0;
    name = 0;
}

/** 
* Create empty animated sprite with count expected frames and sprite index.
* @param count Number of frames to allocate.
* @param spriteIndex Index of the sprite.
*/
AnimatedSprite::AnimatedSprite(byte count, unsigned short spriteIndex){
    type = BaseSprite::st_Animated;

    index = spriteIndex;
    frameCount = count;
    currentFrame = 0;
    frames = new SpriteFrame[count];
    lastUpdate = 0;
    name = 0;
}

/** 
* Gets sprite index of the current frame.
*/
int AnimatedSprite::getFrameIndex(){
    return frames[currentFrame].index;
}

/** 
* Updates the animated sprite. If duration of the frame has exceeded then the
* sprite switches to the next frame.
* @param currentTime The current time.
*/
void AnimatedSprite::update(int currentTime){
    if(currentTime - lastUpdate > frames[currentFrame].duration){
        lastUpdate = currentTime;
        currentFrame++;
        if(currentFrame >= frameCount)
            currentFrame = 0;
        width = frames[currentFrame].sprite->width;
        height = frames[currentFrame].sprite->height;
    }
}

void AnimatedSprite::draw(BaseRenderTarget* target, RenderObject& obj) const{
    for(byte i = 0; i < transformationCounter; i++)
        transformations[i]->apply(obj);

    frames[currentFrame].sprite->draw(target, obj);

}

#ifdef _PC_
void AnimatedSprite::serialize(std::ofstream& destination){
    unsigned char type = 1;
    destination.write((char*) &type, sizeof(type));
    destination.write((char*) &frameCount, sizeof(frameCount));
    for(int f = 0; f < frameCount; f++){
        destination.write((char*) &frames[f].index, sizeof(frames[f].index));
        destination.write((char*) &frames[f].duration, sizeof(frames[f].duration));
    }
}
#endif

void AnimatedSprite::deserialize(MemoryPool* source){
    source->read((char*) &frameCount, sizeof(frameCount));
    frames = new SpriteFrame[frameCount];
    //Load animated sprite frames
    for(int j = 0; j < frameCount; j++){
        source->read((char*) &frames[j].index, sizeof(frames[j].index));
        source->read((char*) &frames[j].duration, sizeof(frames[j].duration));
    }
}

/** 
* Deletes frames from memory.
*/
AnimatedSprite::~AnimatedSprite(){
    for(int i = 0; i < frameCount; i++){
        frames[i].sprite = 0;
    }
    delete frames;
    frames = 0;
}
