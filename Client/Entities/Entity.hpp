#ifndef _ENTITY_
#define	_ENTITY_

#include "Objects/BaseEntity.hpp"
#include "Graphics/RenderTarget.hpp"

#include "../GameResources.hpp"

class Entity:public BaseEntity{
protected:


    float velocityX;
    float velocityY;

    virtual void moveX();
    virtual void moveY();

public:

    /** Entity movement direction. */
    enum Direction{
        dir_None = 0,
        dir_Left = 1,
        dir_Right = 2,
        dir_Up = 4,
        dir_Down = 8
    };

    Map* map;
    
    byte dir;

    float x;
    float y;

    int cWidth;
    int cHeight;
    int cxOffset;
    int cyOffset;

    Entity();

    virtual void update(unsigned int frameTime);
    virtual void draw(RenderTarget& target, unsigned int frameTime);
};

#endif

