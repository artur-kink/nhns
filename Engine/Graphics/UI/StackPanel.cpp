#include "StackPanel.hpp"
#include "Panel.hpp"

StackPanel::StackPanel(int x, int y, int width, int height, int format, int pad):Panel(x,y,width,height,format){
    padding = pad;
}

StackPanel::StackPanel():Panel(0, 0, 1, 1, Panel::Static){
    padding = 1;
}

/** 
* Removes an element from the stack panel.
* The panel is resized and all elements after
* the removed element are pushed upward.
*/
void StackPanel::remove(InterfaceElement* element){
    int index = -1;
    int removeHeight = element->rect.height;
    for(unsigned int i = 0; i < interfaceElements.size(); i++){
        if(interfaceElements.at(i) == element){
            index = i;
            interfaceElements.erase(interfaceElements.begin() + i);
            elements.erase(elements.begin() + i);
            break;
        }
    }
    
    if(index == -1)
        return;
    
    for(unsigned int i = index; i < interfaceElements.size(); i++){
        interfaceElements.at(i)->rect.top -= (removeHeight + padding); 
    }
    rect.height -= (removeHeight + padding);
}

/** 
* Add an element to the top of the stack.
* Resizes the panel and pushes all elements downward.
*/
void StackPanel::addTop(InterfaceElement* element){
    for(unsigned int i = 0; i < interfaceElements.size(); i++){
        interfaceElements.at(i)->rect.top += element->rect.height + padding;
    }
    interfaceElements.insert(interfaceElements.begin(), element);
    elements.insert(elements.begin(), element);
    
    element->parent = this;
    rect.height += element->rect.height + padding;
}

/** 
* Add an element to the bottom of the stack.
* Resizes the panel.
*/
void StackPanel::addBottom(InterfaceElement* element){
    if(interfaceElements.size() > 0)
        element->rect.top = interfaceElements.back()->rect.top + interfaceElements.back()->rect.height + padding;
    else
        element->rect.top = 0;
    
    add(element);
    rect.height += element->rect.height + padding;
}