#include "IconButton.hpp"

IconButton::IconButton():InterfaceElement(0,0,1,1){
    setIcon(0);
}

IconButton::IconButton(int x, int y, int width, int height, BaseSprite* ico):InterfaceElement(x, y, width, height){
	setIcon(ico);
}

void IconButton::setIcon(BaseSprite* ico){
    icon = ico;
}

void IconButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(icon != 0 && visible){
        states.transform *= sf::Transform().translate((float)rect.left, (float)rect.top);
        states.transform *= sf::Transform().scale((float)rect.width/icon->width,(float)rect.height/icon->height);
        target.draw(*icon, states);
    }
}