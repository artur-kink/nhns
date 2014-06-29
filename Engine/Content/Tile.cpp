#include "Tile.hpp"
#include "Utilities/MathHelper.hpp"

/** 
* Initialize an empty tile.
*/
Tile::Tile(){
    clear();
}

/** 
* Get the nth layer of this tile.
*/
unsigned short& Tile::operator[](byte layer){
    return layers[layer];
}

/**
 * Clear all tile layers and properties.
 */
void Tile::clear(){
    properties = 0;
    for(byte i = 0; i < LAYERS; i++){
		layers[i] = NO_SPRITE;
    }
}