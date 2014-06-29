#include "Time.hpp"

Time* Time::instance = 0;

Time::Time(){
    if(instance == 0)
        instance = this;
#ifdef _PC_
    clock.restart();
#endif
    startTimeMillis = getSystemTimeMilliseconds();
    startTimeMicro = getSystemTimeMicroseconds();
}

/**
 * Get the first Time instance created.
 */
Time* Time::getInstance(){
    
    //Create the first Time instance if none exists.
    if(instance == 0)
        new Time();

    return instance;
}

/**
 * Get time since Time has been initialized in milliseconds.
 * This method makes system calls.
 * @return Time in milliseconds.
 */
unsigned int Time::getTimeMilliseconds(){
    return getSystemTimeMilliseconds() - startTimeMillis; 
}

/**
 * Get time since Time has been initialized in microseconds.
 * This method makes system calls.
 * @return Time in microseconds.
 */
unsigned int Time::getTimeMicroseconds(){
    return getSystemTimeMicroseconds() - startTimeMicro; 
}

/**
 * System specific implemntations to get time in milliseconds.
 */
unsigned int Time::getSystemTimeMilliseconds(){
#ifdef _PC_
    return clock.getElapsedTime().asMilliseconds();
#endif
}

/**
 * System specific implemntations to get time in microseconds.
 */
unsigned int Time::getSystemTimeMicroseconds(){
#ifdef _PC_
    return clock.getElapsedTime().asMicroseconds();
#endif
}