#include "AccumulativeTimer.hpp"

AccumulativeTimer::AccumulativeTimer(){
    accumulatedTime = 0;
    lastTime = 0;
    interval = 1000;
}

AccumulativeTimer::AccumulativeTimer(unsigned int t, unsigned int i){
    lastTime = t;
    interval = i;
    accumulatedTime = 0;
}

/**
 * Reset timer.
 * @param t Current time.
 */
void AccumulativeTimer::reset(unsigned int t){
    accumulatedTime = 0;
    lastTime = t;
}

/**
 * Set timer elapse interval.
 * @param i Interval value to set.
 */
void AccumulativeTimer::setInterval(unsigned int i){
    interval = i;
}

/**
 * Check if accumulated time has elapsed the interval.
 * @param t Current time.
 */
bool AccumulativeTimer::hasElapsed(unsigned int t){
    accumulatedTime += (t-lastTime);
    lastTime = t;
    if(accumulatedTime > interval){
        accumulatedTime -= interval;
        return true;
    }
    return false;
}