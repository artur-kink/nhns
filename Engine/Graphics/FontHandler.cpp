#include "FontHandler.hpp"

/**
 * Create an uninitialized font handler.
 * FontHandler::loadFont must be called prior to using this class.
 */
FontHandler::FontHandler(){
    initialized = false;
    fontSize = 64;
}

/**
 * Load font with given name. 
 * All fonts are expected to be .ttf format.
 * @param name Name of font that matches file name, including extension.
 * @return true if font was loaded, false otherwise.
 */
bool FontHandler::loadFont(const char* name){
    initialized = false;
    
#ifdef _PC_
    initialized = font.loadFromFile(name);
    if(!initialized){
        Log << LL_W << LC_F << "Failed to load font: " << name;
    }
#endif
    
    return initialized;
}

#ifdef _PC_
void FontHandler::drawString(sf::RenderTarget& dst, RenderObject& obj, const char* str){
    static sf::Text drawText;
    drawText.setFont(font);

    drawText.setCharacterSize(fontSize);
    drawText.setColor(color);
    drawText.setString(str);
    
    dst.draw(drawText, obj.state);
}
#endif

/**
 * Set the font size.
 */
void FontHandler::setFontSize(byte size){
    fontSize = size;
}

void FontHandler::setFontColor(Color color){
    this->color = color;
}

/**
 * Get the width of the string if it were rendered.
 */
unsigned short FontHandler::getStringWidth(const char* str){
#ifdef _PC_
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(fontSize);
    return text.getLocalBounds().width;
#endif
}