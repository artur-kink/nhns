#ifndef _STATICSPRITE_
#define _STATICSPRITE_

#include "Graphics/BaseSprite.hpp"

/** 
* The most basic sprite that represents a static unchanging part of a texture.
*/
class StaticSprite: public BaseSprite{
protected:
    virtual void draw(BaseRenderTarget* target, RenderObject& obj) const;

public:
#ifdef _PC_
    /** 
    * SFML Representation of the sprite.
    */
    sf::Sprite drawSprite;
#endif

    StaticSprite();
    StaticSprite(int spriteSheet, int spriteIndex, int x, int y, int w, int h);
    

#ifdef _PC_
    StaticSprite(int spriteSheet, int spriteIndex, const sf::Texture& texture, int x, int y, int w, int h);
    virtual sf::Sprite getSprite();
    virtual void serialize(std::ofstream& destination);
#endif

    virtual void deserialize(MemoryPool* source);

    virtual ~StaticSprite();
};

#endif