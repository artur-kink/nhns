#include "GraphicsHandler.hpp"

GraphicsHandler::GraphicsHandler(){
    
}

/**
 * Initialize graphics handler to be ready to draw.
 * This can only be called once.
 * @return true on success, false on error.
 */
bool GraphicsHandler::init(){
    setBackgroundColor(Color::Black);
    return true;
}

/**
 * Specify that a new render cycle is beginning.
 * Set up a new frame to be ready to draw.
 */
void GraphicsHandler::begin(){
#ifdef _PC_
    targetTexture.clear(backgroundColor);
#endif
}

/**
 * Specify that rendering has finished and can be sent to the screen.
 * Copies rendered image to the display.
 */
void GraphicsHandler::end(){
#ifdef _PC_
    targetTexture.display();
    sf::RenderStates state;
    //Copy drawn frame to window.
    rootTarget->draw(targetSprite, state);
    window->display();
#endif
}

/**
 * Set screen background color.
 */
void GraphicsHandler::setBackgroundColor(Color color){
    backgroundColor = color;
}

/**
 * Set display size.
 * @param w New width.
 * @param h New height.
 */
void GraphicsHandler::setSize(unsigned short w, unsigned short h){
    RenderTarget::setSize(w, h);
}

/**
 * Uninitialize graphics and free resources.
 */
void GraphicsHandler::cleanup(){
    Log << LL_D << LC_G << "Closing graphics handler.";
}