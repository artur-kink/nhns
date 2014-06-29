#ifndef _INTERFACEEVENTHANDLER_
#define	_INTERFACEEVENTHANDLER_

#include "InterfaceEvent.hpp"

/** 
* Base class for interface event handlers.
* Any class that wishes to handle interface events should inherit this class.
* Event handlers have to register the events they are capturing by calling
* trap with the EventType that needs to be captured. trapped will be called
* for any event that is raised with the EventTypes marked to be trapped.
* Any implementation of an event handler needs to implement the trapped method.
* If the handler traps a method that it was expecting and this event isn't expected
* to be used anywhere further in the tree, then trapped should return true. If
* the trapped event is not handled then trapped should return false.
* 
* @see InterfaceEvent
* @see InterfaceElement
*/
class InterfaceEventHandler{
protected:
    
    /** 
    * Bitmask of InterfaceEvents that should be trapped.
    */
    unsigned short trapMask;
    
public:
    void trap(const unsigned short event);
    
    virtual void raise(const InterfaceEvent::EventType& event);
    virtual void raise(const InterfaceEvent::EventType& event, void* args);
    virtual void raise(InterfaceEvent* event);
    
    virtual bool trapped(InterfaceEvent* event);
};

#endif