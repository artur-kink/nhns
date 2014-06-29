#ifndef _GRAPHICSHANDLER_
#define _GRAPHICSHANDLER_

#include "Utilities/FileHandler.hpp"
#include "RenderTarget.hpp"
#include "StaticSprite.hpp"

#ifdef _PC_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#endif

/**
 * Main graphics class.
 * Used to draw game.
 */
class GraphicsHandler: public RenderTarget{
    friend class EngineCore;
private:

protected:
    /** Background color. */
    Color backgroundColor;

#ifdef _PC_
    /** The render target that is displayed on screen. */
    sf::RenderTarget* rootTarget;

    /** Game window. */
    sf::RenderWindow* window;
#endif

    void begin();
    void end();

public:
    
    GraphicsHandler();

    bool init();
    void cleanup();

    virtual void setSize(unsigned short w, unsigned short h);
    void setBackgroundColor(Color color);
};

#endif