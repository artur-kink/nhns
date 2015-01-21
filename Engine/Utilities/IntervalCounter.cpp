#include "IntervalCounter.hpp"
#include "Time.hpp"

IntervalCounter::IntervalCounter(){
    setInterval(0);
    
    lastUpdate = 0;
    currentCount = 0;
    previousCount = 0;

    intervalCounter = 1;
    counterTotal = 0;
}

IntervalCounter::IntervalCounter(unsigned int length){
    setInterval(length);

    lastUpdate = 0;
    currentCount = 0;
    previousCount = 0;

    intervalCounter = 1;
    counterTotal = 0;
}

/** 
 * Set counter's interval.
 */
void IntervalCounter::setInterval(unsigned int length){
    interval = length;
}

/**
 * Increment counter. Uses Time::getFrameTime as current time.
 */
void IntervalCounter::increment(){
    increment(Time::getInstance()->getFrameTime());
}

/** 
 * Increment counter.
 * @param time Current time.
 */
void IntervalCounter::increment(unsigned long time){
    currentCount++;
    //If interval has ended start new interval.
    if(time - lastUpdate > interval){
        previousCount = currentCount;
        counterTotal += currentCount;
        intervalCounter++;
        currentCount = 0;
        lastUpdate = time;
    }
}

/**
 * Increases the counter by specified amount.
 * Uses Time::getFrameTime as current time.
 * @param count Amount to increase counter by.
 */
void IntervalCounter::increase(unsigned int count){
    increase(Time::getInstance()->getFrameTime(), count);
}

/** 
 * Increases the counter by specified amount.
 * @param time Current time.
 * @param count Amount to increase counter by.
 */
void IntervalCounter::increase(unsigned long time, unsigned int count){
	currentCount += count;
	//If interval has ended start new interval.
    if(time - lastUpdate > interval){
        previousCount = currentCount;
        counterTotal += currentCount;
        intervalCounter++;
        currentCount = 0;
        lastUpdate = time;
    }
}

/** 
 * Get counter average over all intervals.
 */
unsigned int IntervalCounter::getAverage(){
    return counterTotal/intervalCounter;
}

/** 
 * Get count amount of last full interval.
 */
unsigned int IntervalCounter::getCounter(){
    return previousCount;
}