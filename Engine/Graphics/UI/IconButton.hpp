#ifndef _ICONBUTTON_
#define _ICONBUTTON_

#include "InterfaceElement.hpp"
#include "Graphics/BaseSprite.hpp"


/** 
* A button with an icon. Raises event on left click.
*/
class IconButton:public InterfaceElement{
public:
    BaseSprite* icon;
    IconButton();
    IconButton(int x, int y, int width, int height, BaseSprite* ico);
    void setIcon(BaseSprite* ico);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif