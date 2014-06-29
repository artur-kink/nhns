#include "Rectangle.hpp"

Rectangle::Rectangle(){
    color = Color::Transparent;
}

/**
 * Create Rectangle of given size, position and color.
 */
Rectangle::Rectangle(int x, int y, int w, int h, Color c):InterfaceElement(x, y, w, h){
    color = c;
}

void Rectangle::draw(RenderTarget* target, RenderObject obj) const{
    MatrixTransformation::translate(obj, x, y);
    target->drawRect(obj, width, height, color);
}