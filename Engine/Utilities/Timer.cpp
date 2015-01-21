#include "Timer.hpp"
#include "Time.hpp"

/** 
 * Create a default timer that starts at time 0 and has an interval of 1 second.
 */
Timer::Timer(){
    startTime = 0;
    interval = 1000;
}

/**
 * Create a timer starting at time t with interval of i.
 * @param t Time of timer start.
 * @param i Interval length to track.
 */
Timer::Timer(unsigned int t, unsigned int i){
    startTime = t;
    interval = i;
}

/**
 * Set timer's interval length.
 */
void Timer::setInterval(unsigned int i){
    interval = i;
}

/**
 * Reset timer to current frame time.
 */
void Timer::reset(){
    startTime = Time::getInstance()->getFrameTime();
}

/**
 * Reset timer.
 * @param t Time of reset.
 */
void Timer::reset(unsigned int t){
    startTime = t;
}

/**
 * Check if interval time has elapsed.
 * @return true if elapsed, false otherwise.
 */
bool Timer::hasElapsed(){
    if(Time::getInstance()->getFrameTime() - startTime > interval){
        startTime = Time::getInstance()->getFrameTime();
        return true;
    }
    return false;
}

/**
 * Check if interval time has elapsed.
 * If it has then the timer is reset to given time.
 * @param t Current time.
 * @return true if elapsed, false otherwise.
 */
bool Timer::hasElapsed(unsigned int t){
    if(t - startTime > interval){
        startTime = t;
    	return true;
    }
    return false;
}

/**
 * Check if interval of i has elapsed.
 * This method does not reset the timer.
 * @param t Current time.
 * @param i Interval to check.
 * @return true if elapsed, false otherwise.
 */
bool Timer::hasElapsed(unsigned int t, unsigned int i){
    return t - startTime > i;
}

/**
 * Get amount of time that has elapsed since last reset.
 */
unsigned int Timer::getElapsedTime(){
    return Time::getInstance()->getFrameTime() - startTime;
}

/**
 * Get the amount of time that has elapsed since last reset.
 * @param t Current time. 
 */
unsigned int Timer::getElapsedTime(unsigned int t){
    return t - startTime;
}

/**
 * Get the amount of time elapsed as a ratio of interval.
 * @return ElapsedTime/Interval
 */
float Timer::getElapsedRatio(){
    return (float)getElapsedTime()/(float)interval;
}

/**
 * Get the amount of time elapsed as a ratio of interval.
 * @param t Current time.
 * @return ElapsedTime/Interval
 */
float Timer::getElapsedRatio(unsigned int t){
    return (float)getElapsedTime(t)/(float)interval;
}