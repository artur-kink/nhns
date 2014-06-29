#ifndef _LAYEREDSPRITE_
#define _LAYEREDSPRITE_
#include "BaseSprite.hpp"
#include "DynamicSprite.hpp"
#include <cstring>

/** 
* A sprite composed of multiple sprites drawn ontop of each other.
*/
class LayeredSprite : public BaseSprite {
private:
protected:
    virtual void draw(BaseRenderTarget* target, RenderObject& obj) const;
public:
    /** 
    * Sprite layers.
    */
    BaseSprite** layers;

    /** 
    * Number of layers.
    */
    byte layerCount;

    LayeredSprite(byte count, unsigned short spriteIndex);
    virtual void update(int currentTime);

#ifdef _PC_
    virtual void serialize(std::ofstream& destination);
#endif

    virtual void deserialize(MemoryPool* source);

    virtual ~LayeredSprite();
};

#endif

