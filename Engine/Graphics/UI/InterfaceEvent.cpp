#include "InterfaceEvent.hpp"

/** 
 * Create empty event.
 */
InterfaceEvent::InterfaceEvent(){
    source = 0;
    args = 0;
}

/** 
 * Create an event with type, source and arguments.
 * @param eventType Type of event.
 * @param src Pointer to InterfaceElement that raised this event.
 * @param eventArgs Address to argument. This argument should not be deleted or lost from scope
 * before the event is handled.
 */
InterfaceEvent::InterfaceEvent(EventType eventType, void* src, void* eventArgs){
    type = eventType;
    source = src;
    args = eventArgs;
}

/** 
 * Copy an event.
 * @param copy Copy source.
 */
InterfaceEvent::InterfaceEvent(const InterfaceEvent& copy){
    type = copy.type;
    source = copy.source;
    args = copy.args;
}

/** 
 * Delete event. Does not delete source or args.
 */
InterfaceEvent::~InterfaceEvent(){
    source = 0;
    args = 0;
}