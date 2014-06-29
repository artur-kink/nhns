#ifndef _RENDEROBJECT_
#define _RENDEROBJECT_


#ifdef _PC_
#include <SFML/Graphics.hpp>
#endif

typedef struct _RenderObject{
#ifdef _PC_
        int sourceWidth;
        int sourceHeight;
        sf::RenderStates state;
        sf::Sprite sprite;
#endif
        _RenderObject(){
#ifdef _PC_
            state =  sf::RenderStates::Default;
#endif
        }
    } RenderObject;

#endif