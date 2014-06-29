#include "Color.hpp"

Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
Color Color::Transparent = Color(1.0f, 1.0f, 1.0f, 0.0f);

/**
 * Create default black color.
 */
Color::Color(){
    Color(0, 0, 0, 1);
}

/**
 * Create color with given values, no transparency.
 */
Color::Color(float r, float g, float b){
    Color(r, g, b, 1.0f);
}

/**
 * Create color with all values supplied.
 */
Color::Color(float r, float g, float b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

#ifdef _PC_
/**
 * Color to SFML::Color conversion.
 */
Color::operator sf::Color(){
    return sf::Color(255*r, 255*g, 255*b, 255*a); 
}
#endif