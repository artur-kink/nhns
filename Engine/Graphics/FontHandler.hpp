#ifndef _FONTHANDLER_
#define _FONTHANDLER_

#include <cstring>

#include "Types.hpp"
#include "Color.hpp"
#include "BaseRenderTarget.hpp"
#include "Utilities/FileHandler.hpp"

#ifdef _PC_
#include <SFML/Graphics.hpp>
#endif

/**
 * Class used to draw fonts.
 * The FontHandler is designed to use only one font,
 * if more fonts are needed then separate FontHandlers
 * should be initialized.
 */
class FontHandler{
private:

    /** Name of font. */
    char fontName[25];

    /** Is the font loaded and ready to use. */
    bool initialized;

    /** Size of font. */
    byte fontSize;

    /** Font color. */
    Color color;
public:
#ifdef _PC_
    /** SFML Font implementation. */
    sf::Font font;
#endif
    FontHandler();

    bool loadFont(const char* name);

    unsigned short getStringWidth(const char* str);
    void setFontSize(byte size);
    void setFontColor(Color color);
#ifdef _PC_
    void drawString(sf::RenderTarget& dst, RenderObject& obj, const char* str);
#endif

};

#endif