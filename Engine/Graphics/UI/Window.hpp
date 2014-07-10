#ifndef _WINDOW_
#define _WINDOW_

#include "IconButton.hpp"
#include "InterfaceElement.hpp"
#include "Label.hpp"
#include "Panel.hpp"
#include "Rectangle.hpp"

/** 
* A UI Window. Stores other UI elements.
*/
class Window:public InterfaceElement{
protected:
    
    Panel contentPanel;
    Panel topBar;
    Label title;
    
    bool isMoving;
    int moveOffsetX;
    int moveOffsetY;

    Rectangle background;
    
public:
    Window();

    void setTitle(std::string t);

    virtual void draw(RenderTarget* target, RenderObject obj) const;
    virtual bool trapped(InterfaceEvent* event);
    virtual InterfaceElement* collisionCheck(int x, int y);
    virtual void setSize(int width, int height);

    virtual void add(InterfaceElement* element);
    virtual void update(unsigned int time);
    
    virtual ~Window();
};

#endif