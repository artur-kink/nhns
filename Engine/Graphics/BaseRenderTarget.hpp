#ifndef _BASERENDERTARGET_
#define _BASERENDERTARGET_

#include "RenderObject.hpp"

#ifdef _PC_
#include <SFML/Graphics.hpp>
#endif

/**
 * Base class for classes that can be rendered to.
 */
class BaseRenderTarget{
public:
    virtual void draw(RenderObject& object) = 0;
};

#endif