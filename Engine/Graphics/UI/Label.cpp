#include "Label.hpp"

FontHandler Label::fontHandler;
bool Label::fontLoaded = false;

Label::Label():InterfaceElement(0, 0, 100, 12){
    if(!fontLoaded){
        fontLoaded = fontHandler.loadFont("arial.ttf");
    }
    setString(12, Color::White, "");
}

Label::Label(int x, int y, int fontSize, Color fontColor, std::string text)
   :InterfaceElement(x, y, 0, 0){
   Label();
   setString(fontSize, fontColor, text);
}

Label::Label(int x, int y, int fontSize, Color fontColor):InterfaceElement(x, y, 0, 0){
   Label();
   setString(fontSize, fontColor, "");
}

Label::Label(int fontSize, Color fontColor, std::string text):InterfaceElement(0, 0, 0, 0){
    Label();
    setString(fontSize, fontColor, text);
}

void Label::setString(std::string text){
    string = text;
}

void Label::setString(int fontSize, Color fontColor, std::string text){
    
    fontHandler.setFontSize(fontSize);
    fontHandler.setFontColor(fontColor);
    setString(text);
}

void Label::draw(RenderTarget* target, RenderObject obj) const{
    target->setFont(&fontHandler);
    MatrixTransformation::translate(obj, x, y);
    target->drawString(string.c_str(), obj);
}

std::string Label::getString(){
    return string;
}