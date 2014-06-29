#include "Graphics/SpriteManager.hpp"
#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/LogManager.hpp"

int main(int argc, char** argv){
    StringHelper::init();
    Log >> new ConsoleLogger();
    //Set filter to include all.
    Log.setLevelFilter(LogManager::ll_Verbose);
    for(int i = 1; i < argc; i+=2){
        Log << argv[i] << " to " << argv[i+1];
        SpriteManager manager;
        manager.loadRaw(argv[i]);
        manager.save(argv[i+1]);
    }
    Log.close();
    return 0;
}