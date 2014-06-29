#ifndef _UIMANAGER_
#define _UIMANAGER_

#include <vector>
#include "InterfaceElement.hpp"
#include "KeyboardElement.hpp"
#include "Panel.hpp"
#include "Label.hpp"

using namespace std;

/** 
* The UIManager is responsible for handling input to the UI, raising UI events
* and drawing all UI elements.
* update should be called on each frame with a frame time, and the mouse information.
* keyEvent should be called whenever there is keyboard input that needs to be
* handled by the UI.
* resize should be called whenever the window has been resized.
* If a user of the UIManager wishes to capture events in the UI, then it must be
* an InterfaceEventHandler and set as the parentHandler in the UIManager.
* @see InterfaceElement
* @see InterfaceEvent
* @see InterfaceEventHandler
*/
class UIManager : public InterfaceElement {
private:
    
    /** 
    * Element being left pressed.
    */
    InterfaceElement* leftDownElement;
    
    /** 
    * Element being right pressed.
    */
    InterfaceElement* rightDownElement;
    
    /** 
    * List of all elements in the UI.
    */
    vector<InterfaceElement*> elements;
    
    /** 
    * Element that has keyboard input.
    */
    KeyboardElement* keyboardElement;

    /** 
    * Time of last left click.
    */
    unsigned int lastLeftClick;
    
    /** 
    * Last element to be left clicked.
    */
    InterfaceElement* lastLeftClickElement;

    /** 
    * Was left mouse button down on the previous update.
    */
    bool prevLeftDown;
    
    /** 
    * Was right mouse button down on the previous update.
    */
    bool prevRightDown;
    
    /** 
    * X location on last update.
    */
    int prevX;
    
    /** 
    * Y location on last update.
    */
    int prevY;
public:
    
    /** 
    * Event handler that the UIManager should pass events on to.
    */
    InterfaceEventHandler* parentHandler;
    
    /** 
    * Does the UI hold keyboard input.
    */
    bool hasKeyboard;
    
    /** 
    * Element currently being hovered over.
    */
    InterfaceElement* hoverElement;

    UIManager();

    void addElement(InterfaceElement* element);
    void removeElement(InterfaceElement* element);
    bool update(unsigned int time, int x, int y, bool leftDown, bool rightDown);

    void keyEvent(sf::Uint32 key);
    void wheelEvent(int delta);
    void giveKeyboard(KeyboardElement* element);
    void takeKeyboard();

    virtual void raise(InterfaceEvent* event);

    virtual void onResize(int w, int h);
    virtual void draw(RenderTarget* target, RenderObject obj) const;
    virtual void draw(RenderTarget* target) const;

    void clear();
};

#endif