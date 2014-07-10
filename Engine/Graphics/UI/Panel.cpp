#include "Panel.hpp"

Panel::Panel(int x, int y, int w, int h, int format):InterfaceElement(x, y, w, h){
    formatType = format;
}

Panel::Panel(){
    formatType = Panel::Static;
	setPosition(0, 0);
	setSize(100, 100);
}

/** 
* Add an interface element to the panel.
*/
void Panel::add(InterfaceElement* element){
    interfaceElements.push_back(element);
    element->parent = this;
}

/** 
* Remove an interface element from the panel.
*/
void Panel::remove(InterfaceElement* element){
    for (unsigned int i = 0; i < interfaceElements.size(); i++) {
        if (interfaceElements.at(i) == element) {
            interfaceElements.erase(interfaceElements.begin() + i);
            break;
        }
    }
}

/**
 * Remove all interface elements in the panel.
 */
void Panel::clear(){
    interfaceElements.clear();
}

InterfaceElement* Panel::collisionCheck(int x, int y){
    if(!InterfaceElement::collisionCheck(x, y))
        return 0;
    
    //Check for collision on any element in panel.
    for(unsigned int i = 0; i < interfaceElements.size(); i++){
        if(interfaceElements.at(i)->visible){
            InterfaceElement* collisionElement;
            collisionElement = interfaceElements.at(i)->collisionCheck(x - this->x, y - this->y);
            if(collisionElement != 0)
                return collisionElement;
        }
    }
    
    return this;
}

void Panel::draw(RenderTarget* target, RenderObject obj) const {
    MatrixTransformation::translate(obj, x, y);
    for(unsigned int i = 0; i < interfaceElements.size(); i++){
        if(interfaceElements.at(i)->visible)
            interfaceElements.at(i)->draw(target, obj);
    }
}

void Panel::update(unsigned int time){
    for(unsigned int i = 0; i < interfaceElements.size(); i++){
        interfaceElements.at(i)->update(time);
    }
}

void Panel::setFormat(byte type){
    formatType = type;
}

void Panel::onResize(int w, int h){
    //Check if panel needs to resize.
    if(formatType & Panel::VerticalStretch)
        height = h;
    if(formatType & Panel::HorizontalStretch)
        width = w;
    if(formatType & Panel::BindBottom)
        y = h - height;
    if(formatType & Panel::BindRight)
        x = w - width;
    
    //Update panel contents incase size changed.
    for(unsigned int i = 0; i < interfaceElements.size(); i++){
        interfaceElements.at(i)->onResize(width, height);
    }
}

Panel::~Panel(){
    clear();
}