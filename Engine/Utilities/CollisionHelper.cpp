#include "CollisionHelper.hpp"

/**
 * Check for intersection between two rectangles, parametarized.
 * @param x1 Rect 1 x position.
 * @param y1 Rect 1 y position.
 * @param w1 Rect 1 width.
 * @param h1 Rect 1 height.
 * @param x2 Rect 2 x position.
 * @param y2 Rect 2 y position.
 * @param w2 Rect 2 width.
 * @param h2 Rect 2 height.
 * @return true if rectangles intersect, false otherwise.
 */
inline bool CollisionHelper::collides(int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2){
    return (((x1 >= x2 && x1 <= x2 + w2) || (x2 >= x1 && x2 <= x1 + w1)) &&
        ((y1 >= y2 && y1 <= y2 + h2) || (y2 >= y1 && y2 <= y1 + h1)));
}

/**
 * Check for collision between an entity and a region.
 * @return true if collide, false otherwise.
 *//*
bool CollisionHelper::collides(Region* region, Entity* entity){
    return CollisionHelper::collides(region->x, region->y, region->width, region->height,
            entity->x + entity->cxOffset, entity->y + entity->cyOffset, entity->cWidth, entity->cHeight);
}*/

/**
 * Check for collision between two regions.
 * @return true if collide, false otherwise.
 */
bool CollisionHelper::collides(Region* region1, Region* region2){
    return CollisionHelper::collides(region1->x, region1->y, region1->width, region1->height,
            region2->x, region2->y, region2->width, region2->height);
}

/**
 * Check for collision between to entities.
 * @return true if collide, false otherwise.
 *//*
bool CollisionHelper::collides(Entity* entity1, Entity* entity2){
    return CollisionHelper::collides(entity1->x + entity1->cxOffset, entity1->y + entity1->cyOffset, entity1->cWidth, entity1->cHeight,
            entity2->x + entity2->cxOffset, entity2->y + entity2->cyOffset, entity2->cWidth, entity2->cHeight);
}
*/
/**
 * Check for collision between entity and a point (x,y)
 * @param x Point x location.
 * @param y Point y location.
 * @return true if point is in entity, false otherwise.
 *//*
bool CollisionHelper::collides(Entity* entity, int x, int y){
    return (entity->x + entity->cxOffset <= x && entity->y + entity->cyOffset <= y &&
            entity->x + entity->cxOffset + entity->cWidth >= x && entity->y + entity->cyOffset + entity->cHeight >= y);
}
*/
/**
 * Check for collision between region and a point (x,y)
 * @param x Point x location.
 * @param y Point y location.
 * @return true if point is in region, false otherwise.
 */
bool CollisionHelper::collides(Region* region, int x, int y){
    return (region->x <= x && region->y <= y &&
            region->x + region->width >= x && region->y + region->height >= y);
}