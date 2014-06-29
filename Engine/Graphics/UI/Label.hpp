#ifndef _LABEL_
#define _LABEL_

#include "Graphics/FontHandler.hpp"
#include "InterfaceElement.hpp"


/** 
* A text field container.
*/
class Label:public InterfaceElement{
protected:
    static FontHandler fontHandler;
    static bool fontLoaded;

    std::string string;
public:

    Label();
    Label(int fontSize, Color color, std::string text);
    Label(int x, int y, int fontSize, Color color);
    Label(int x, int y, int fontSize, Color color, std::string text);
    
    virtual void setString(std::string text);
    virtual void setString(int fontSize, Color fontColor, std::string text);
    std::string getString();

    virtual void draw(RenderTarget* target, RenderObject obj) const;
};

#endif