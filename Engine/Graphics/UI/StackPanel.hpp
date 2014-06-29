#ifndef _STACKPANEL_
#define	_STACKPANEL_

#include "Panel.hpp"

/** 
///A panel that stacks elements vertically.
*/
class StackPanel:public Panel{
protected:
    
    /** 
    ///Padding between stacked elements.
    */
    int padding;
    
public:
    
    StackPanel();
    StackPanel(int x, int y, int width, int height, int format, int pad);
    virtual void addTop(InterfaceElement* element);
    virtual void addBottom(InterfaceElement* element);
    virtual void remove(InterfaceElement* element);
};


#endif

