#include "RenderedSprite.hpp"

RenderedSprite::RenderedSprite(){
    type = BaseSprite::st_Static;
    init(32, 32);
}

RenderedSprite::RenderedSprite(int w, int h){
    type = BaseSprite::st_Static;
    init(w, h);
}

void RenderedSprite::init(int w, int h){
	width = w;
	height = w;
    texture.create(width, height);
    texture.display();
    texture.clear(sf::Color::Transparent);
    textureSprite.setTexture(texture.getTexture(), true);
}

void RenderedSprite::clear(){
	texture.clear(sf::Color::Transparent);
	texture.display();
}

void RenderedSprite::render(BaseSprite* sprite){
    texture.draw(*sprite, sf::RenderStates::Default);
    texture.display();
}

void RenderedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(textureSprite, states);
}

RenderedSprite::~RenderedSprite(){
    
}