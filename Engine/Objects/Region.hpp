#ifndef _REGION_
#define	_REGION_

#include <cstring>
#include "Types.hpp"
#include "BaseObject.hpp"

#define REGION_NAME_LENGTH 15 /** Maximum name length of region. Region array length + 1. */

/**
 * An area on the map.
 */
class Region:public BaseObject{
friend class RegionManager;
protected:
public:
    /** X position of region.*/
    int x;
    /** Y position of region.*/
    int y;

    /** Width of region.*/
    unsigned short width;
    /** Height of region.*/
    unsigned short height;

    /** Region name, the unique identifier of a region.*/
    char name[REGION_NAME_LENGTH+1];

	/** Has the region changed position. */
	bool dirty;

    Region();
    Region(int tx, int ty, unsigned short w, unsigned short h);

    virtual void setName(const char* n);
    virtual void setArea(int tx, int ty, unsigned short w, unsigned short h);
};

#endif

