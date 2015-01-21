#include "Label.hpp"

Label::Label():InterfaceElement(0, 0, 100, 12){
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

/**
 * Set font of this label.
 */
void Label::setFont(FontHandler* fontHandler){
    font = fontHandler;
}

void Label::draw(RenderTarget* target, RenderObject obj) const{
    MatrixTransformation::translate(obj, x, y);
    target->setFont(font);
    font->setFontSize(size);
    font->setFontColor(color);
    target->drawString(string.c_str(), obj);
}

std::string Label::getString(){
    return string;
}