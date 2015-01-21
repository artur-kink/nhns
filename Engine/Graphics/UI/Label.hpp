#ifndef _LABEL_
#define _LABEL_

#include "Graphics/FontHandler.hpp"
#include "InterfaceElement.hpp"


/** 
* A text field container.
*/
class Label:public InterfaceElement{
protected:

    FontHandler* font;
    
    Color color;
    byte size;

    std::string string;
public:

    Label();
    Label(int fontSize, Color color, const char* text);
    Label(int x, int y, int fontSize, Color color);
    Label(int x, int y, int fontSize, Color color, const char* text);
    
    virtual void setString(const char* text);
    virtual void setString(int fontSize, Color fontColor, const char* text);
    std::string getString();

    void setFont(FontHandler* fontHandler);
    
    virtual void draw(RenderTarget* target, RenderObject obj) const;
};

#endif