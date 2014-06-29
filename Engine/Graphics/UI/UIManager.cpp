#include "UIManager.hpp"

/** 
* Create empty UI manager.
*/
UIManager::UIManager(): InterfaceElement(){
    rightDownElement = 0;
    leftDownElement = 0;
    hoverElement = 0;
    keyboardElement = 0;
    hasKeyboard = false;

    parentHandler = 0;
    
    lastLeftClickElement = 0;
    prevLeftDown = false;
    prevRightDown = false;
    prevX = 0;
    prevY = 0;
}

/** 
* Event reached UI Manager meaning its unhandled, release it.
*/
void UIManager::raise(InterfaceEvent* event){
    if(parentHandler)
        parentHandler->raise(event);
    else
        delete event;
}

/** 
* Add an element to the UI.
*/
void UIManager::addElement(InterfaceElement* element){
    element->parent = this;
    elements.push_back(element);
}

/** 
* Remove an element from the UI.
*/
void UIManager::removeElement(InterfaceElement* element){
    for(unsigned int i = 0; i < elements.size(); i++){
        if(elements.at(i) == element){
            elements.erase(elements.begin() + i);
            break;
        }
    }
}

/** 
* Draw the entire UI.
*/
void UIManager::draw(RenderTarget* target) const{
    RenderObject obj;
    draw(target, obj);
}

void UIManager::draw(RenderTarget* target, RenderObject obj) const{
    for(unsigned int i = 0; i < elements.size(); i++){
        if(elements.at(i)->visible)
            elements.at(i)->draw(target, obj);
    }
}

void UIManager::wheelEvent(int delta){
    if(hoverElement){
        hoverElement->raise(InterfaceEvent::MouseWheelMoved, &delta);
    }
}

/** 
* Have UI handle a key input event.
*/
void UIManager::keyEvent(sf::Uint32 key){
    if(keyboardElement){
        keyboardElement->keyEvent(key);
        if(!keyboardElement->hasKeyboard()){
            takeKeyboard();
        }
    }
}

/** 
* Give control of keyboard to the UI.
*/
void UIManager::giveKeyboard(KeyboardElement* element){
    if(keyboardElement != 0 && keyboardElement != element){
        takeKeyboard();
    }
    if(keyboardElement != element){
        keyboardElement = element;
        keyboardElement->giveKeyboard();
        hasKeyboard = true;
    }
}

/** 
* Take control of keyboard from UI.
*/
void UIManager::takeKeyboard(){
    if(keyboardElement != 0){
        keyboardElement->takeKeyboard();
        hasKeyboard = false;
        keyboardElement = 0;
    }
}

/** 
* Updates UI and events.
*/
bool UIManager::update(unsigned int time, int x, int y, bool leftDown, bool rightDown){

    bool returnVal = false;

    //Check if right button was pressed and released.
    if(rightDownElement != 0 && !rightDown){
        rightDownElement->raise(InterfaceEvent::RightClick);
        rightDownElement = 0;
    }

    //Check if a hover element is still being hovered on.
    if(hoverElement != 0){
        if(!hoverElement->collisionCheck(x, y)){
            hoverElement->raise(InterfaceEvent::MouseOut);
            hoverElement = 0;
        }
    }

    //If an element has keyboard and mouse has been pressed
    //take control of keyboard away.
    if(keyboardElement != 0 && leftDown){
        takeKeyboard();
    }

    //Check for input collision on element in UI.
    bool collisionDone = false;
    for(int i = elements.size() - 1; i >= 0; i--){
        if(elements.at(i)->visible){
            elements.at(i)->update(time);
            InterfaceElement* collisionElement;
            collisionElement = elements.at(i)->collisionCheck(x, y);
            if(collisionElement && !collisionDone){
                if(leftDown){
                    if(!prevLeftDown){
                        leftDownElement = collisionElement;
                        leftDownElement->raise(InterfaceEvent::LeftPressed);
                    }
                }else{
                    if(leftDownElement == collisionElement){
                        if(lastLeftClickElement == collisionElement && (time - lastLeftClick) < 500){
                            collisionElement->raise(InterfaceEvent::DoubleClick);
                        }else{
                            lastLeftClickElement = collisionElement;
                            collisionElement->raise(InterfaceEvent::LeftClick);
                        }

                        if(leftDownElement->keyboard){
                            giveKeyboard(dynamic_cast<KeyboardElement*> (leftDownElement));
                        }else if(keyboardElement != 0){
                            takeKeyboard();
                        }

                        lastLeftClick = time;
                        leftDownElement->raise(InterfaceEvent::LeftReleased);
                    }else if(leftDownElement != 0){
                        leftDownElement->raise(InterfaceEvent::LeftReleased);
                    }
                    leftDownElement = 0;
                }

                if(rightDown){
                    rightDownElement = collisionElement;
                    rightDownElement->raise(InterfaceEvent::RightClick);
                }else{
                    if(rightDownElement == collisionElement){
                        collisionElement->raise(InterfaceEvent::RightClick);
                    }
                }

                if(!rightDown && !leftDown){
                    hoverElement = collisionElement;
                }

                //We only allow one element to be interacted with.
                returnVal = true;
                collisionDone = true;
            }
        }
    }
    
    if(!collisionDone){
        if(leftDownElement != 0 && !leftDown){
            leftDownElement->raise(InterfaceEvent::LeftReleased);
            leftDownElement = 0;
        }
    }
    prevX = x;
    prevY = y;
    prevLeftDown = leftDown;
    prevRightDown = rightDown;
    return returnVal;
}

/** 
* Tell all elements in the UI that the screen has resized.
*/
void UIManager::onResize(int w, int h){
    for(unsigned int i = 0; i < elements.size(); i++){
        elements.at(i)->onResize(w, h);
    }
}

/** 
* Removes all elements in the UI.
*/
void UIManager::clear(){
    hoverElement = 0;
    lastLeftClickElement = 0;
    leftDownElement = 0;
    rightDownElement = 0;
    keyboardElement = 0;
    elements.clear();
}