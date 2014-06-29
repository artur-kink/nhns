#ifndef _INTERFACEELEMENT_
#define _INTERFACEELEMENT_

#include "Types.hpp"
#include "Graphics/RenderTarget.hpp"
#include "Graphics/MatrixTransformation.hpp"
#include "InterfaceEventHandler.hpp"

/** 
* Base class for all user interface elements.
* All interface elements should inherit this class. Any element that needs
* to be drawn or updated should be added to a UIManager.
* All interface elements should implement draw.
* If the element needs to be updated periodically, update should be implemented.
* @see InterfaceEventHandler
* @see InterfaceEvent
*/
class InterfaceElement:public InterfaceEventHandler{
    friend class UIManager;

public:
    
    /** 
    * Parent that contains this element.
    */
    InterfaceElement* parent;

    /** 
    * Is this element visible.
    */
    bool visible;
    
    /** 
    * Is this a keyboard element.
    */
    bool keyboard;
 
    /**
     * Position of element.
     */
    int x, y;
    /**
     * Size of element.
     */
    int width, height;

    InterfaceElement();
    InterfaceElement(int x, int y, int width, int height);

    virtual InterfaceElement* collisionCheck(int x, int y);

    virtual void raise(InterfaceEvent* event);
    virtual void raise(const InterfaceEvent::EventType& event);
    virtual void raise(const InterfaceEvent::EventType& event, void* args);
    
    /** 
    * Update this element.
    */
    virtual void update(unsigned int time){};
    
    virtual void draw(RenderTarget* target, RenderObject obj) const = 0;

    virtual void setRect(int x, int y, int width, int height);
    virtual void setPosition(int x, int y);
    virtual void setSize(int w, int h);

    /** 
    * Method called when an interface event's parent has been resized.
    */
    virtual void onResize(int width, int height){};
    
    virtual ~InterfaceElement();
};

#endif