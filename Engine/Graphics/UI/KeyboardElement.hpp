#ifndef _KEYBOARDELEMENT_
#define _KEYBOARDELEMENT_

#include "SFML/Window.hpp"
#include "InterfaceElement.hpp"

/** 
* An element that handles keyboard input.
*/
class KeyboardElement{
protected:
    bool hasInput;
public:

    KeyboardElement(){
        hasInput = false;;
    }
    virtual void keyEvent(sf::Uint32 key) = 0;
    virtual bool hasKeyboard() = 0;
    virtual void giveKeyboard() = 0;
    virtual void takeKeyboard() = 0;
};

#endif