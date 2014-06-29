#ifndef _TIME_
#define _TIME_

#ifdef _PC_
#include "SFML/System/Clock.hpp"
#endif


/**
 * Real time tracking class.
 * Used to get system time since the initialization of class.
 * This class is not used to get time such as Date/
 */
class Time{
private:

#ifdef _PC_
    sf::Clock clock;
#endif

    /** First Time class created. */
    static Time* instance;

    unsigned long startTimeMicro;
    unsigned int startTimeMillis;

    unsigned int getSystemTimeMilliseconds();
    unsigned int getSystemTimeMicroseconds();
public:
    Time();

    static Time* getInstance();

    unsigned int getTimeMilliseconds();
    unsigned int getTimeMicroseconds();
};

#endif