#include "Server.hpp"

/** 
 * Initializes a new instance of the Server class.
 */
Server::Server(){
    Log << LL_D << LC_E << "Initializing Engine core.";
    StringHelper::init();
    MathHelper::init();
}

/**
 * 
 */
void Server::start(){
    running = true;
    
    Time currentTime;
    AccumulativeTimer updateTimer;
    updateTimer.setInterval(25000);
    updateTimer.reset(currentTime.getTimeMicroseconds());

    while(running){

         //Run server update in a semi fixed step format.
        while(updateTimer.hasElapsed(currentTime.getTimeMicroseconds())){
            unsigned int frameTime = currentTime.getTimeMilliseconds();
            Log << LL_V << LC_E << "Running Update";
            update(frameTime);
        }
    }
}

void Server::update(unsigned long frameTime){
    
}

void Server::stop(){

}