#include "Entity.hpp"

Entity::Entity(){
    x = y = 0;
}

void Entity::update(unsigned int frameTime){

    if(dir & (int)Entity::dir_Up)
        y--;
    else if(dir & (int)Entity::dir_Down)
        y++;

    if(dir & (int)Entity::dir_Right)
        x--;
    else if(dir & (int)Entity::dir_Left)
        x++;
    
}

void Entity::draw(RenderTarget& target, unsigned int frameTime){
    target.draw(Resources->sprites.getSprite("character"), x, y);
}