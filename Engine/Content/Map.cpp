#include "Map.hpp"

/**
 * Create a new map with given name and size;
 * @param mapName String name of map.
 * @param mapWidth Width of map in tiles.
 * @param mapHeight Height of map in tiles.
 * @todo replace std::string with const char*
 */
Map::Map(std::string mapName, unsigned short mapWidth, unsigned short mapHeight){
    name = mapName;
    width = mapWidth;
    height = mapHeight;

    tiles = new Tile[width*height];
}

/**
 * Clear all map tiles.
 */
void Map::clear(){
    for(unsigned int t = 0; t < width*height; t++){
        tiles[t].clear();
    }
}

/**
 * Copy given map to this map at given position.
 * @param src Map to copy from.
 * @param x X tile to start copying to.
 * @param y Y tile to start copying to.
 */
void Map::copy(Map* src, int x, int y){
    for(unsigned short h = 0; h < src->height && h + y < height; h++){
        for(unsigned short w = 0; w < src->width && w + x < width; w++){
            getTile(w + x, h + y) = src->getTile(w, h);
        }
    }
}

/**
 * Get the n'th tile in map array.
 */
Tile& Map::operator[](unsigned short tile){
    return tiles[tile];
}

/**
 * Get tile at x,y coordinates.
 * @param x X coordinate of tile.
 * @param y Y coordinate of tile.
 */
Tile& Map::getTile(unsigned short x, unsigned short y){
	return tiles[x + y*width];
}

Map::~Map(){
    delete tiles;
    tiles = 0;
}