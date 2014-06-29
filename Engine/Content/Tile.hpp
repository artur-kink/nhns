#ifndef _TILE_
#define	_TILE_

#include "Types.hpp"
#include <cstdlib>
#include <time.h>

#define LAYERS 5
#define NO_SPRITE 65535

/** 
* A map tile.
*/
class Tile{
public:
    
    /** 
    * Tile property type enum.
    */
    enum TileType{
        t_BlockTop = 0x01,
        t_BlockRight = 0x02,
        t_BlockBottom = 0x04,
        t_BlockLeft = 0x08,
        t_BlockAll = 0x0F
    };
    
    /** 
    * Layer sprite indeces.
    */
    unsigned short layers[LAYERS];
    
    /** 
    * Layer properties bitmap. See TileType.
    */
    byte properties;
    
    Tile();
    
    unsigned short& operator[](byte layer);

    void clear();
};

#endif