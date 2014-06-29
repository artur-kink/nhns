#ifndef _RENDEREDSPRITE_
#define	_RENDEREDSPRITE_

#include "BaseSprite.hpp"

class RenderedSprite: public BaseSprite{
protected:
    sf::Sprite textureSprite;

#ifdef _PC_
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
#endif
public:
    sf::RenderTexture texture;
    
    RenderedSprite();
    RenderedSprite(int w, int h);
    
    void init(int w, int h);
	void clear();
    void render(BaseSprite* sprite);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual ~RenderedSprite();
};

#endif

