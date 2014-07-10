#ifndef _ENGINECORE_
#define _ENGINECORE_

#ifdef _PC_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#endif

#include "Types.hpp"
#include "Utilities/FileLogger.hpp"
#include "Utilities/InputHandler.hpp"
#include "Utilities/FileHandler.hpp"
#include "Utilities/Time.hpp"
#include "Utilities/AccumulativeTimer.hpp"
#include "Graphics/GraphicsHandler.hpp"
#include "Utilities/MathHelper.hpp"

/**
 * Core engine code. Initializes all the engine subsystems
 * and manages the interaction between them and the game.
 * 
 * The main game class must implement the EngineCore.
 * 
 * The update and draw calls must be implemented to update the game
 * state and draw the game state respectively. The update and draw calls
 * are not synchronized, meaning the fps does not equal updates per second.
 * The engine update call is implemented in a semi fixed step, thus each 
 * update call is "guaranteed" to run every 20ms, and no delta time implementation
 * is required. 
 */
class EngineCore{
private:

    /** Is engine running. */
    bool engineRunning;

protected:
    /** Graphics handler. */
    GraphicsHandler graphics;
    InputHandler input;

#ifdef _PC_
    /** SFML graphics window. */
    sf::RenderWindow window;

    bool hasFocus;
#endif

#ifdef _PC_
    virtual void sfmlEvent(sf::Event event);
#endif

    EngineCore();

    void run();
public:

    /** Initialize engine and all subsystems. */
    virtual void init();
    /**
    * Update engine state.
    * @param frameTime Time of update.
    */
    virtual void update(unsigned int frameTime) = 0;
    
    /**
     * Base draw call.
     * @param frameTime Time of draw.
     */
    virtual void draw(unsigned int frameTime) = 0;

    virtual void start();
    virtual void stop();

    virtual void resolutionChanged(int width, int height);
};

#endif