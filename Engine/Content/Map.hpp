#ifndef _MAPC_
#define _MAPC_
#include <string>
#include <iostream>
#include "Tile.hpp"
#include "Types.hpp"

/** 
* Game map.
*/
class Map{
    friend class MapResizer;
public:
    unsigned short width, height;
    
    /** Name of map. */
    std::string name;
    /** Array of tiles in map. */
    Tile* tiles;

    Map(std::string mapName, unsigned short mapWidth, unsigned short mapHeight);
    
    void clear();
    void copy(Map* src, int x, int y);
    Tile& operator[](unsigned short tile);
    Tile& getTile(unsigned short x, unsigned short y);

    ~Map();
};
#endif