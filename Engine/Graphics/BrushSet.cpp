#include "BrushSet.hpp"

BrushSet::BrushSet(){
    tiles = 0;
}

BrushSet::BrushSet(byte num){
    numTiles = num;
    tiles = new BrushTile[numTiles];
}

BrushSet::~BrushSet(){
    if(tiles){
        delete tiles;
        tiles = 0;
    }
}