#ifndef _RECTANGLE_
#define _RECTANGLE_

#include "InterfaceElement.hpp"

/**
 * An UI element that draws a rectangle.
 */
class Rectangle:public InterfaceElement{
public:
    Color color;

    Rectangle();
    Rectangle(int x, int y, int w, int h, Color c);

    virtual void draw(RenderTarget* target, RenderObject obj) const;
};

#endif