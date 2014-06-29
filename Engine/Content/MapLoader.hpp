#ifndef _MAPLOADER_
#define _MAPLOADER_
#ifdef _PC_
#include "pugixml.hpp"
#include <string>
#include <iostream>
#include <fstream>
#endif

#include "Map.hpp"
#include "Utilities/FileHandler.hpp"
#include "Utilities/StringHelper.hpp"
#include "Graphics/SpriteManager.hpp"
#include "Objects/RegionManager.hpp"

using namespace std;

/** 
 * Static class used for loading and saving maps.
 */
class MapLoader{
	
public:
    static bool loadMap(const char* fileName, Map** map, RegionManager* regions);
#ifdef _PC_
    static void saveMap(Map* map, RegionManager* regionManager);
    static bool loadRawMap(const char* fileName, Map** map, SpriteManager* sprites, RegionManager* regions);
    static void saveRawMap(Map* map, SpriteManager* sprites, RegionManager* regions);
#endif

};
#endif