#ifndef _INTERFACEEVENT_
#define _INTERFACEEVENT_

/** 
* An event raised by an InterfaceElement.
* An interface event includes the original source of the event and
* an EventType that specifies what kind of event it is.
* Events are created by the UIManager and raised on the elements
* that created them. An event should never delete the source, or
* the args passed to the element.
* 
* @see InterfaceElement
* @see InterfaceEventHandler
*/
class InterfaceEvent{

public:
    /** 
    * Type of event raised by the UI.
    */
    enum EventType{
        /** 
        * Left click registerred on an element.
        */
        LeftClick = 1,
        /** 
        * Right click registerred on an element.
        */
        RightClick = 2,
        /** 
        * Double left click registerred on an element.
        */
        DoubleClick = 4,
        /** 
        * Element received keyboard control.
        */
        GotKeyboard = 8,
        /** 
        * Element lost keyboard control.
        */
        LostKeyboard = 16,
        /** 
        * Element released its keyboard control.
        */
        ReleasedKeyboard = 32,
        /** 
        * Mouse has entered an element.
        */
        MouseOver = 64,
        /** 
        * Mouse has exited an element.
        */
        MouseOut = 128,
        /** 
        * Left mouse has been pressed.
        */
        LeftPressed = 256,
        /** 
        * Left mouse has been released.
        */
        LeftReleased = 512,
        /** 
        * Mouse wheel has moved.
        */
        MouseWheelMoved = 1024,
        /** 
        * Custom Element event.
        */
        Custom = 2048
    };

    /** 
    * Event type.
    */
    EventType type;

    /** 
    * Element that raised event.
    */
    void* source;
    
    /** 
    * Arguments associated with the given event.
    */
    void* args;

    InterfaceEvent();
    InterfaceEvent(EventType eventType, void* src, void* eventArgs);
    InterfaceEvent(const InterfaceEvent& copy);
    
    ~InterfaceEvent();
};

#endif