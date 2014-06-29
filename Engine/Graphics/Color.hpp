#ifndef _COLOR_
#define _COLOR_

#ifdef _PC_
#include "SFML/Graphics.hpp"
#endif

/**
 * Basic color structure containing RGB + Alpha information.
 */
class Color{
public:

    static Color Black;
    static Color Blue;
    static Color Green;
    static Color Red;
    static Color White;
    static Color Transparent;

    /** Red value. */
    float r;
    /** Green value. */
    float g;
    /** Blue value. */
    float b;
    /** Alpha value. */
    float a;

    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
#ifdef _PC_
    operator sf::Color();
#endif
};

#endif