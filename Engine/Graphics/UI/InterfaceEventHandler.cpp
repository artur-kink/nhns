#include "InterfaceEventHandler.hpp"

/** 
* Raise an event for this handler. This method should delete the passed event if
* the event is not passed on further.
* @param event The event to raise
*/
void InterfaceEventHandler::raise(InterfaceEvent* event){
    if(event->type & trapMask){
        trapped(event);
    }
    delete event;
}

void InterfaceEventHandler::raise(const InterfaceEvent::EventType& event, void* args){
    raise(new InterfaceEvent(event, this, args));
}

/** 
* Raise an event.
* @param event Event type to raise
*/
void InterfaceEventHandler::raise(const InterfaceEvent::EventType& event){
    raise(new InterfaceEvent(event, this, 0));
}

/** 
* Mark event type to be trapped.
* @param event EventType that should be trapped.
*/
void InterfaceEventHandler::trap(const unsigned short event){
    trapMask = trapMask | event;
}

/** 
* Called if a raised event is marked as trapped.
* If event is handled returns true, else false.
* @param event Trapped event.
*/
bool InterfaceEventHandler::trapped(InterfaceEvent* event){
    //Default implementation, do nothing.
    return false;
}