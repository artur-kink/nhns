#ifndef _RENDERTARGET_
#define _RENDERTARGET_

#include "ShaderTransformation.hpp"

#ifdef _PC_
#include <SFML/Graphics.hpp>
#endif

#include "BaseSprite.hpp"
#include "FontHandler.hpp"
#include "BaseRenderTarget.hpp"
#include "Camera.hpp"

class RenderTarget:public BaseRenderTarget{
protected:
    FontHandler* defaultFont;
    Camera* camera;
    
#ifdef _PC_
    sf::RenderTexture targetTexture;
    sf::Sprite targetSprite;
#endif
    
public:

    /** Width of render target. */
    unsigned short width;
    /** Height of render target. */
    unsigned short height;

    RenderTarget();
    
    virtual void setSize(unsigned short w, unsigned short h);

    virtual void draw(RenderObject& object);
    virtual void drawRect(RenderObject obj, int w, int h, Color color);
    virtual void draw(BaseSprite* sprite, int x, int y);
    virtual void draw(BaseSprite* sprite, RenderObject obj = RenderObject());
    virtual void drawString(const char* str, RenderObject obj = RenderObject());
    virtual void draw(RenderTarget* target, RenderObject obj = RenderObject());
    
    virtual void clear(float r, float g, float b);
    virtual void clear(Color color);
    void setFont(FontHandler* font);
    void setCamera(Camera* c);
};

#endif