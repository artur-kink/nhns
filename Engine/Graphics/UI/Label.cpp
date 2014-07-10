#include "Label.hpp"

FontHandler Label::fontHandler;
bool Label::fontLoaded = false;

Label::Label():InterfaceElement(0, 0, 100, 12){
    if(!fontLoaded){
        fontLoaded = fontHandler.loadFont("arial.ttf");
    }
    setString(12, Color::White, "");
}

Label::Label(int x, int y, int fontSize, Color fontColor, const char* text)
   :InterfaceElement(x, y, 0, 0){
   Label();
   setString(fontSize, fontColor, text);
}

Label::Label(int x, int y, int fontSize, Color fontColor):InterfaceElement(x, y, 0, 0){
   Label();
   setString(fontSize, fontColor, "");
}

Label::Label(int fontSize, Color fontColor, const char* text):InterfaceElement(0, 0, 0, 0){
    Label();
    setString(fontSize, fontColor, text);
}

void Label::setString(const char* text){
    string = text;
}

void Label::setString(int fontSize, Color fontColor, const char* text){
    size = fontSize;
    color = fontColor;
    setString(text);
}

void Label::draw(RenderTarget* target, RenderObject obj) const{
    MatrixTransformation::translate(obj, x, y);
    target->setFont(&fontHandler);
    fontHandler.setFontSize(size);
    fontHandler.setFontColor(color);
    target->drawString(string.c_str(), obj);
}

std::string Label::getString(){
    return string;
}