#ifndef _TANDEMTIMER_
#define	_TANDEMTIMER_

#include "Types.hpp"

/** 
 * The TandemTimer is a one-two timer that keeps track of two sequential time
 * intervals.
 * The timer contains two intervals and an interval counter. 
 * At reset the timer counts the first interval s times(as specified
 * in setIntervals). Once the first interval has elapsed s times then
 * the timer begins counting the second interval. At reset the timer
 * resets to the first interval.
 */
class TandemTimer{
private:
    /** Timer start time. */
    unsigned int startTime;

    /** Length of first time interval. */
    unsigned int firstInterval;

    /** Length of second time interval. */
    unsigned int secondInterval;
    
    /** Current interval being timed. */
    unsigned int currentInterval;
   
    /** Number of times the first interval has to elapse before switching to second interval. */ 
    byte switchCount;
    /** Number of times the first interval has elapsed since reset. */
    byte switchCounter;
    
public:
    
    TandemTimer();
    
    void setIntervals(byte s, unsigned int first, unsigned int second);
    void reset(unsigned int time);
    bool hasElapsed(unsigned int time);
    
};

#endif

