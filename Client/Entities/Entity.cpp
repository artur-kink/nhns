#include "Entity.hpp"

Entity::Entity(){
    x = y = 0;
    velocityX = velocityY = 0;
    cWidth = cHeight = 8;
    cxOffset = cyOffset = 0;
}

void Entity::moveX(){

    //Backup current location and move character.
	float tX = x;
	x += velocityX;

    //Get collision box location
    float cX = x + cxOffset;

    unsigned short tileX = 0;
    //Check horizontal movement collision.
	if(velocityX){
		if(velocityX < 0){
			tileX = (unsigned short)(cX/TILESIZE);
			if(tileX >= map->width || map->getTile(tileX, (y + cyOffset)/TILESIZE).properties ||
				map->getTile(tileX, (y + cyOffset+cHeight)/TILESIZE).properties){
				x = tX;
				velocityX = 0;
			}

		}else{
			tileX = (unsigned short)(cX + cWidth)/TILESIZE;
			if(tileX >= map->width || map->getTile(tileX, (y + cyOffset)/TILESIZE).properties ||
				map->getTile(tileX, (y + cyOffset+cHeight)/TILESIZE).properties){
				x = tX;
				velocityX = 0;
			}
		}
	}
}

void Entity::moveY(){
    //Backup current location and move character.
	float tY = y;
	y += velocityY;

    //Get collision box location
    float cY = y + cyOffset;

    unsigned short tileY = 0;
    //Check vertical movement collision
	if(velocityY){
		if(velocityY < 0){
			tileY = (unsigned short)(cY/TILESIZE);
			if(tileY >= map->height || map->getTile((int)(x + cxOffset)/TILESIZE, tileY).properties ||
				map->getTile((int)(x + cxOffset+cWidth)/TILESIZE, tileY).properties){
				y = tY;
				velocityY = 0;
			}

		}else{
			tileY = (unsigned short)((cY+cHeight)/TILESIZE);
			if(tileY >= map->height || map->getTile((int)(x + cxOffset)/TILESIZE, tileY).properties ||
				map->getTile((int)(x + cxOffset+cWidth)/TILESIZE, tileY).properties){
				y = tY;
				velocityY = 0;
			}
		}
	}
}

void Entity::update(unsigned int frameTime){

    if(dir & (int)Entity::dir_Up)
        velocityY = -1;
    else if(dir & (int)Entity::dir_Down)
        velocityY = 1;
    else
        velocityY = 0;

    if(dir & (int)Entity::dir_Right)
        velocityX = -1;
    else if(dir & (int)Entity::dir_Left)
        velocityX = 1;
    else
        velocityX = 0;
    
    moveX();
    moveY();
}

void Entity::draw(RenderTarget& target, unsigned int frameTime){
    target.draw(Resources->sprites.getSprite("character"), x, y);
}