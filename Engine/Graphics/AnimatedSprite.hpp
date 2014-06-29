#ifndef _ANIMATEDSPRITE_
#define _ANIMATEDSPRITE_

#include "BaseSprite.hpp"
#include "DynamicSprite.hpp"


/** 
* A frame in an animated sprite.
*/
struct SpriteFrame {
    unsigned short index;
    BaseSprite* sprite;
    unsigned short duration;
};

/** 
* An animated sprite composed of timed frames consisting of other sprites.
*/
class AnimatedSprite : public DynamicSprite {
protected:
    virtual void draw(BaseRenderTarget* target, RenderObject& obj) const;
public:
    /** 
    * Frames in this sprite.
    */
    SpriteFrame* frames;

    /** 
    * Number of frames.
    */
    byte frameCount;

    /** 
    * The frame index being currently shown.
    */
    byte currentFrame;

    AnimatedSprite();
    AnimatedSprite(byte count, unsigned short spriteIndex);
    int getFrameIndex();
    virtual void update(int currentTime);

#ifdef _PC_
    virtual void serialize(std::ofstream& destination);
#endif

    virtual void deserialize(MemoryPool* source);

    virtual ~AnimatedSprite();
};

#endif