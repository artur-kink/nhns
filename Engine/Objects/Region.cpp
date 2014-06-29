#include "Region.hpp"

/**
 * Initialize blank region.
 */
Region::Region():BaseObject(){
    name[0] = 0;
    x = y = 0;
    index = 0;
    width = height = 1; //Set to 1 to avoid potential divide by 0.
}

Region::Region(int tx, int ty, unsigned short w, unsigned short h){
    setArea(tx, ty, w, h);
}

/**
 * Set the region name.
 * @param n New name of region.
 */
void Region::setName(const char* n){
    strncpy(name, n, REGION_NAME_LENGTH);
    name[REGION_NAME_LENGTH] = 0; //Ensure null terminator.
}

/**
 * Set the size and location of a Region.
 * @param tx X location.
 * @param ty Y location.
 * @param w Width.
 * @param h Height.
 */
void Region::setArea(int tx, int ty, unsigned short w, unsigned short h){
    //Ensure non 0 area to avoid potential divide by 0.
    if(w == 0)
        w = 1;
    if(h == 0)
        h = 1;

    x = tx;
    y = ty;
    width = w;
    height = h;
}