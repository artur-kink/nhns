#include "Graphics/SpriteManager.hpp"
#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/LogManager.hpp"
#include "Content/MapLoader.hpp"

int main(int argc, char** argv){
    StringHelper::init();
    Log >> new ConsoleLogger();
    //Set filter to include all.
    Log.setLevelFilter(LogManager::ll_Verbose);
    SpriteManager manager;
    manager.load("Content/sprites.dat");
    for(int i = 1; i < argc; i++){
        Log << argv[i];
        Map* map = 0;
        RegionManager regions;
        MapLoader::loadRawMap(argv[i], &map, &manager, &regions);
        MapLoader::saveMap(map, &regions);
    }
    Log.close();
    return 0;
}
