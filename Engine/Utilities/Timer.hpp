#ifndef _TIMER_
#define _TIMER_

/**
 * A basic time tracking structure.
 * Used to keep track of the amount of time that has
 * passed since the last reset call. Can also be used to
 * check if a time interval has passed since last reset
 * by either setting a default interval or passing desired interval.
 * All inputs of time should be from the same source.
 */
class Timer{
private:
    /** Timer starting time. */
    unsigned int startTime;

    /** Length of the time interval since start until timer has elapsed. */
    unsigned int interval;
public:
    Timer();
    Timer(unsigned int t, unsigned int i);

    
    unsigned int getElapsedTime(unsigned int t);
    bool hasElapsed(unsigned int t);
    bool hasElapsed(unsigned int t, unsigned int i);
    
    void setInterval(unsigned int i);
    void reset(unsigned int t);    
};

#endif
