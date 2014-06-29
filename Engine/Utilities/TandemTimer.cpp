#include "TandemTimer.hpp"

/** 
* Instantiate non counting timer.
*/
TandemTimer::TandemTimer(){
    firstInterval = secondInterval = 0;
    switchCounter = 0;
    switchCount = 1;
}

/** 
 * Set timer intervals and the switch count.
 * @param s Number of times the first interval should be counted.
 * @param first Length of first interval.
 * @param second Length of second interval.
 */
void TandemTimer::setIntervals(byte s, unsigned int first, unsigned int second){
    switchCount = s;
    firstInterval = first;
    secondInterval = second;
}

/** 
 * Reset timer time and interval to the first interval.
 * @param time Current time.
 */
void TandemTimer::reset(unsigned int time){
    startTime = time;
    currentInterval = firstInterval;
    switchCounter = 0;
}

/** 
 * Check if an interval time has elapsed. Switches to next interval timing if true.
 * @param time Current time.
 * @return true if current interval has elapsed, false otherwise.
 */
bool TandemTimer::hasElapsed(unsigned int time){
    if(time - startTime > currentInterval){
        
        if(switchCounter >= switchCount){
            currentInterval = secondInterval;
        }else{
            switchCounter++;
        }
        
        startTime = time;
        return true;
    }
    return false;
}
