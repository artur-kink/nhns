#ifndef _INTERVALCOUNTER_
#define _INTERVALCOUNTER_

/** 
* A counter used to keep track of a count per interval of time.
*/
class IntervalCounter{
private:
    
    /** Time of last interval update.*/
    unsigned long lastUpdate;
    
    /** Length of interval in milliseconds.*/
    unsigned int interval;
    
    /** Count of previous interval.*/
    unsigned int previousCount;
    
    /** Count in this interval.*/
    unsigned int currentCount;

    /** Total number of intervals counted.*/
    unsigned int intervalCounter;
    
    /** Total number of counts in all intervals. */
    unsigned int counterTotal;
public:
    
    IntervalCounter();
    IntervalCounter(unsigned int length);
    
    void setInterval(unsigned int length);
    void increment(unsigned long time);
	void increase(unsigned long time, unsigned int count);
    unsigned int getAverage();
    unsigned int getCounter();
};

#endif