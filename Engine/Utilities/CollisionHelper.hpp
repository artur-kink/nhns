#ifndef _COLLISIONHELPER_
#define	_COLLISIONHELPER_

#include "Objects/BaseEntity.hpp"
#include "Objects/Region.hpp"

/**
 * Helper class to evaluate collision.
 */
class CollisionHelper{
public:
    inline static bool collides(int x1, int y1, int w1, int h1,
            int x2, int y2, int w2, int h2);
    //static bool collides(Region* region, Entity* entity);
    static bool collides(Region* region1, Region* region2);
    //static bool collides(Entity* entity1, Entity* entity2);
    //static bool collides(Entity* entity, int x, int y);
    static bool collides(Region* region, int x, int y);
};

#endif