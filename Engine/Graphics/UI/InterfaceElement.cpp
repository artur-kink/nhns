#include "InterfaceElement.hpp"

InterfaceElement::InterfaceElement(int x, int y, int width, int height){
    visible = true;
    setRect(x, y, width, height);
    keyboard = false;
    parent = 0;
    trapMask = 0;
}

/** 
* Default constructor creates empty element.
*/
InterfaceElement::InterfaceElement(){
    parent = 0;
    keyboard = false;
    visible = true;
    trapMask = 0;
}

/** 
* Set the size and position of this element.
* @param x The x.
* @param y The y.
* @param width The width.
* @param height The height.
*/
void InterfaceElement::setRect(int x, int y, int width, int height){
    setPosition(x, y);
    setSize(width, height);
}

/** 
* Set position of this element.
* @param x X Position
* @param y Y Position
*/
void InterfaceElement::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

/** 
* Sets the size of this element.
* @param w The width.
* @param h The height.
*/
void InterfaceElement::setSize(int w, int h){
    width = w;
    height = h;
}

/** 
* Check if given x,y coordinates are within the rectangular area of this element.
* @param x X Location to check against.
* @param y Y Location to check against.
* @return Pointer to the element where the collision occurred or 0 if none occurred.
*/
InterfaceElement* InterfaceElement::collisionCheck(int x, int y){
    if(!visible)
        return 0;
    
    if(x < this->x + width && x > this->x &&
            y < this->y + height && y > this->y)
                return this;
    
    return 0;
}

/** 
* Raise an event.
* @param event The event to raise
*/
void InterfaceElement::raise(InterfaceEvent* event){
    if(event->type & trapMask){
        //If event is trapped clear and return, else propagate further.
        if(trapped(event)){
            delete event;
            return;
        }
    }
    
    //If the event was not trapped, raise it if there is a parent.
    if(parent)
        parent->raise(event);
    else
        delete event;
}

/** 
* Raise an event.
* @param event The event to raise
*/
void InterfaceElement::raise(const InterfaceEvent::EventType& event){
    InterfaceElement::raise(new InterfaceEvent(event, this, 0));
}

void InterfaceElement::raise(const InterfaceEvent::EventType& event, void* args){
    InterfaceElement::raise(new InterfaceEvent(event, this, args));
}

InterfaceElement::~InterfaceElement(){
    parent = 0;
}