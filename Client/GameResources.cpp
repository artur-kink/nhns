#include "GameResources.hpp"

GameResources* GameResources::instance = 0;

GameResources::GameResources(){
}

GameResources::~GameResources(){
    audio.stopAll();
}

GameResources* GameResources::I(){
    if(!instance)
        instance = new GameResources();
    return instance;
}