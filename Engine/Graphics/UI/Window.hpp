#ifndef _WINDOW_
#define _WINDOW_

#include "IconButton.hpp"
#include "ScrollPanel.hpp"
#include "InterfaceElement.hpp"
#include "Label.hpp"

/** 
* A UI Window. Stores other UI elements.
*/
class Window:public InterfaceElement{
protected:
    
    Panel contentPanel;
    Panel topBar;
    Label title;
    IconButton closeButton;
    bool isMoving;
    int moveOffsetX;
    int moveOffsetY;

    sf::RectangleShape background;
public:
    Window();

    void setTitle(std::string t);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual bool trapped(InterfaceEvent* event);
    virtual InterfaceElement* collisionCheck(int x, int y);
    virtual void setSize(int width, int height);

    virtual void add(InterfaceElement* element);
    virtual void update(unsigned int time);
    
    virtual ~Window();
};

#endif