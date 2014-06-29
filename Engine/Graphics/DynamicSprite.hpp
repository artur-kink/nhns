#ifndef _DYNAMICSPRITE_
#define _DYNAMICSPRITE_


/** 
* Base class for a sprite that requires updating.
*/
class DynamicSprite: public BaseSprite{
protected:
    /** Time since last update.*/
    long lastUpdate;
    
public:
    /** 
    * Updates the sprite.
    * @param currentTime The current time.
    */
    virtual void update(int currentTime) = 0;
};

#endif