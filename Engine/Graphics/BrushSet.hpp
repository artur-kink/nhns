#ifndef _BRUSHSET_
#define _BRUSHSET_

#include "BaseSprite.hpp"

/**
 * A brush set is a set of sprites each with their own position.
 * A brush set can be used to specify multiple sets and how 
 * they should be drawn together.
 */
class BrushSet{
public:
    struct BrushTile{
        BaseSprite* sprite;
        byte x;
        byte y;
    };

    /**
     * List of tiles in this brush set.
     */
    BrushTile* tiles;

    /**
     * Number of tiles in this set.
     */
    byte numTiles;

    BrushSet();
    BrushSet(byte num);
    ~BrushSet();
};

#endif