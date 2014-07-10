#include "TextBox.hpp"

TextBox::TextBox(int x, int y, int width, int height, int maxLen, int fontSize, Color color):Label(x, y, fontSize, color),KeyboardElement(){
    setSize(width, height);
    maxLength = maxLen;
    hasCursor = false;
    hasInput = false;
    keyboard = true;
    lastInput = 0;
    cursorIndex = 0;
    keyboardTimer.setIntervals(5, 250, 100);
}

TextBox::TextBox():Label(0, 0, 12, Color::White){
    maxLength = 25;
    hasCursor = false;
    hasInput = false;
    keyboard = true;
    lastInput = 0;
    cursorIndex = 0;
    keyboardTimer.setIntervals(5, 250, 100);
}

/**
* Trigger key event for the textbox.
*/
void TextBox::keyEvent(sf::Uint32 key){
    lastInput = key;
    if(key == 8){ //Backspace
        if(text.length() > 0 && cursorIndex > 0){
            if(cursorIndex == 1){
                setString(text.substr(1, text.length() - 1).c_str());
            }else if(cursorIndex == text.length()){
                setString(text.substr(0, text.length() - 1).c_str());
            }else{
                setString((text.substr(0, cursorIndex - 1) + text.substr(cursorIndex, text.length() - cursorIndex)).c_str());
                cursorIndex--;
            }

        }
    }else if(key == 127){ //Delete
        if(text.length() > 0 && cursorIndex < text.length()){
            if(cursorIndex == 0){
                setString(text.substr(1, text.length() - 1).c_str());
            }else if(cursorIndex == text.length() - 1){
                setString(text.substr(0, text.length() - 1).c_str());
            }else{
                setString((text.substr(0, cursorIndex) + text.substr(cursorIndex+1, text.length() - cursorIndex)).c_str());
            }

        }
    }else if(key == 27 || key == 13){//Enter or escape
        releaseKeyboard();
    }else if(key >= 32 && key <= 126 && text.length() < maxLength){//Text input

        if(cursorIndex == 0){
            text = std::string((char)key + text);
        }else if(cursorIndex == text.length()){
            text += key;
        }else{
            text = text.substr(0, cursorIndex) + (char)key + text.substr(cursorIndex, text.length() - cursorIndex);
        }
        setString(text.c_str());
        cursorIndex++;
    }
}

bool TextBox::hasKeyboard(){
    return hasInput;
}

void TextBox::giveKeyboard(){
    hasInput = true;
    raise(InterfaceEvent::GotKeyboard);
}

void TextBox::takeKeyboard(){
    hasCursor = false;
    hasInput = false;
    setString(text.c_str());
    cursorIndex = text.length();
    raise(InterfaceEvent::LostKeyboard);
}

void TextBox::releaseKeyboard(){
    hasCursor = false;
    hasInput = false;
    setString(text.c_str());
    cursorIndex = text.length();
    raise(InterfaceEvent::ReleasedKeyboard);
}

void TextBox::update(unsigned int time){
    if(hasInput){
        if(time - cursorTimer > 250){//Update cursor flash.
            cursorTimer = time;

            char cursor = ' ';
            if(hasCursor){
                cursor = '|';
            }

            //Parse string and place cursor in proper location.
            if(cursorIndex == 0){
                Label::setString((cursor + text).c_str());
            }else if(cursorIndex == text.length()){
                Label::setString((text + cursor).c_str());
            }else{
                Label::setString((text.substr(0, cursorIndex) + cursor + text.substr(cursorIndex, text.length() - cursorIndex)).c_str());
            }
            hasCursor = !hasCursor;
        }

        //Check for other keyboard input(Arrow keys)
        if(keyboardTimer.hasElapsed(time)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if(cursorIndex < text.length()){
                    cursorIndex++;
                }
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if(cursorIndex > 0){
                    cursorIndex--;
                }
            }else{
                keyboardTimer.reset(time);
            }
        }
    }
}

void TextBox::setString(const char* value){
    text = value;
    Label::setString(value);
    if(cursorIndex > text.length())
        cursorIndex = text.length();
}

void TextBox::setString(int fontSize, Color fontColor, const char* text){
    Label::setString(fontSize, fontColor, text);
    setString(text);
}

void TextBox::clear(){
    text.clear();
    cursorIndex = 0;
    setString(text.c_str());
}

TextBox::~TextBox(){
}