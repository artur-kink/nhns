#include "RenderTarget.hpp"

RenderTarget::RenderTarget(){
    camera = 0;
#ifdef _PC_
    targetSprite.setTexture(targetTexture.getTexture(), true);
#endif
}

void RenderTarget::draw(RenderObject& object){
    if(camera){
        float xScale = (float)width/(float)camera->width;
        float yScale = (float)height/(float)camera->height;

#ifdef _PC_
        
#endif
    }
#ifdef _PC_
    targetTexture.draw(object.sprite, object.state);
#endif
}


/** 
 * Draw rectangle with given parameters.
 */
void RenderTarget::drawRect(RenderObject obj, int w, int h, Color color){
#ifdef _PC_
    //Create draw rectangle.
    sf::RectangleShape rect;
    rect.setFillColor(color);
    
    if(camera){
        float xScale = (float)width/(float)camera->width;
        float yScale = (float)height/(float)camera->height;
        rect.setSize(sf::Vector2f(w, h));
        sf::Transform scale;
        scale.scale(xScale, yScale);
        scale.combine(obj.state.transform);
        obj.state.transform =  scale;
        obj.state.transform.translate(-camera->x, -camera->y);
    }else{
        rect.setSize(sf::Vector2f(w, h));
    }
    //Draw rectangle.
    targetTexture.draw(rect, obj.state);
#endif
}


/**
 * Set size of render target.
 */
void RenderTarget::setSize(unsigned short w, unsigned short h){
    width = w;
    height = h;
#ifdef _PC_
    targetTexture.create(width, height);
    targetSprite.setTexture(targetTexture.getTexture(), true);
#endif
}

/**
 * Draw a sprite on this RenderTarget.
 */
void RenderTarget::draw(BaseSprite* sprite, int x, int y){
#ifdef _PC_
    RenderObject obj;
    if(camera){
        float xScale = (float)width/(float)camera->width;
        float yScale = (float)height/(float)camera->height;
        obj.state.transform.scale(xScale, yScale);
        obj.state.transform.translate(x - camera->x, y - camera->y);
    }else{
        obj.state.transform.translate(x, y);
    }

    sprite->draw(this, obj);
#endif
}

/**
 * Draw a sprite on this RenderTarget.
 */
void RenderTarget::draw(BaseSprite* sprite, RenderObject obj){
#ifdef _PC_
    if(camera){
        float xScale = (float)width/(float)camera->width;
        float yScale = (float)height/(float)camera->height;
        sf::Transform original = obj.state.transform;
        obj.state.transform = sf::Transform();
        obj.state.transform.scale(xScale, yScale);
        obj.state.transform.combine(original);
        obj.state.transform.translate(-camera->x, -camera->y);
    }

    sprite->draw(this, obj);
#endif
}

void RenderTarget::draw(RenderTarget* target, RenderObject obj){
#ifdef _PC_
    target->targetTexture.display();
    targetTexture.draw(target->targetSprite, obj.state);
#endif
}

/**
 * Draw a string to the render target.
 * This method uses the current defaultFont, which
 * can be set using RenderTarget::setFont.
 * The main draw work should be implemented inside FontHandler.
 */
void RenderTarget::drawString(const char* str, RenderObject obj){
#ifdef _PC_
    if(camera){
        float xScale = (float)width/(float)camera->width;
        float yScale = (float)height/(float)camera->height;
        sf::Transform original = obj.state.transform;
        obj.state.transform = sf::Transform();
        obj.state.transform.scale(xScale, yScale);
        obj.state.transform.combine(original);
        obj.state.transform.translate(-camera->x, -camera->y);
    }
    defaultFont->drawString(targetTexture, obj, str);
#endif
}

/**
 * Set the FontHandler to use for drawing fonts.
 */
void RenderTarget::setFont(FontHandler* font){
    defaultFont = font;
}

void RenderTarget::setCamera(Camera* c){
    camera = c;
}

void RenderTarget::clear(Color color){
#ifdef _PC_
    targetTexture.clear(color);
#endif
}

void RenderTarget::clear(float r, float g, float b){
#ifdef _PC_
    sf::Color color;
    color.r = r*255;
    color.g = g*255;
    color.b = b*255;
    targetTexture.clear(color);
#endif
}