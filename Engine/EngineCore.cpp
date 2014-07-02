#include "EngineCore.hpp"

EngineCore::EngineCore(){
    //Create an error log.
    //FileLogger* errorLogger = new FileLogger("error");
    //errorLogger->lockFilter();
    //Log >> errorLogger;

    init();
}

/**
* Start running the engine.
* Any override of this method has to call this base method at the end.
*/
void EngineCore::start(){
    engineRunning = true;
    run();
}

/**
* Stop running the engine.
* Any override of this method has to call this base method at the end.
*/
void EngineCore::stop(){
    Log << LL_D << LC_E << "Stopping engine.";
    engineRunning = false;
    graphics.cleanup();
}

/**
 * Initialize engine and all subsystems.
 * 
 */
void EngineCore::init(){
    Log << LL_D << LC_E << "Initializing Engine core.";
    StringHelper::init();
    MathHelper::init();
    graphics.init();

#ifdef _PC_
    window.create(sf::VideoMode(1280, 720), "Title", sf::Style::Default);

    graphics.window = &window;
    graphics.rootTarget = &window;

    input.window = &window;
#endif
    
    Log << LL_D << LC_E << "Engine core initialized";
}

/**
 * The main game loop.
 */
void EngineCore::run(){

    Log << LL_V << LC_E << "Running Engine";

    Time currentTime;
    AccumulativeTimer updateTimer;
    updateTimer.setInterval(25000);
    updateTimer.reset(currentTime.getTimeMicroseconds());

    while(engineRunning){
        
        //Run engine update in a semi fixed step format.
        while(updateTimer.hasElapsed(currentTime.getTimeMicroseconds())){
            unsigned int frameTime = currentTime.getTimeMilliseconds();
            Log << LL_V << LC_E << "Running frame Update";
            input.update(frameTime);
            update(frameTime);
        }

        unsigned int frameTime = currentTime.getTimeMilliseconds();
        Log << LL_V << LC_G << "Beginning draw";
        graphics.begin();
        draw(frameTime);
        graphics.end();
        Log << LL_V << LC_G << "Finished draw";

#ifdef _PC_

        //Check if engine should continue running
        sf::Event event;
        while(window.pollEvent(event)){
            // Close window : exit
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::Resized){
                resolutionChanged(window.getSize().x, window.getSize().y);
            }
            
        }
        
        if(!window.isOpen()){
            engineRunning = false;
        }
        sf::sleep(sf::milliseconds(1));
#endif
    }

    Log << LL_D << LC_E << "Shutting down";
}

void EngineCore::resolutionChanged(int width, int height){
}
