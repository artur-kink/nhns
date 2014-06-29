#ifndef _BASESPRITE_
#define _BASESPRITE_

#ifdef _PC_
#include "SFML/Graphics.hpp"
#endif

#ifdef _DEVTOOL_
#include <cstring>
#endif

#include "Types.hpp"
#include "BaseRenderTarget.hpp"
#include "BaseTransformation.hpp"
#include "Utilities/Serializable.hpp"

#ifndef NO_SPRITE
#define NO_SPRITE 65535
#endif

/** 
 * A base class for all Sprites.
 * These classes are used to encapsulate all drawable sprites.
 */
class BaseSprite:public Serializable{
    friend class AnimatedSprite;
    friend class StaticSprite;
    friend class LayeredSprite;

    friend class RenderTarget;
    friend class GraphicsHandler;
protected:

    /** Gets the draw specifics of a the sprite. Returned by arg pointer. */    
    virtual void draw(BaseRenderTarget* target, RenderObject& obj) const = 0;

public:

    /** 
    * The sprite's type.
    */
    enum SpriteType{
        /** A static unchangeable sprite. */
        st_Static,
        /** A compilation of multiple sprites. */
        st_Layered,
        /** An animated sprite that is a collection of static sprites. */
        st_Animated
	};
    
    /** 
    * Sprite index in the full sprite list.
    */
    unsigned short index;

    /** 
    * Spritesheet index.
    */
    int sheet;

    /** 
    * The sprite's type.
    */
    SpriteType type;


    /** 
    * Pointer to the name of the sprite.
    * Note that this pointer is shared with the spriteNames list
    * of SpriteManager. The names are managed by the sprite manager
    * and therefore this pointer should not be allocated or released.
    */
    char* name;

    /** 
     * The size of this sprite. This is specifically useful in the dynamic sprites.
     */
    int width, height;

    int x, y;

    /**
     * An array of transformations applied to this sprite.
     */
    BaseTransformation* transformations[16];

    /**
     * Number of currently applied transformations.
     */
    byte transformationCounter;

    BaseSprite();

    virtual void apply(BaseTransformation* transformation);
#ifdef _PC_
    virtual void serialize(std::ofstream& destination) = 0;
#endif
    virtual void deserialize(MemoryPool* source) = 0;
    virtual ~BaseSprite();
};

#endif