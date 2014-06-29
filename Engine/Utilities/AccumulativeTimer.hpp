#ifndef _ACCUMULATIVETIMER_
#define _ACCUMULATIVETIMER_

/**
 * A timer that accumulates time, with any extra time since
 * an elapsed interval being put forward to the next interval.
 */
class AccumulativeTimer{
private:
    /** Last time elapsed check was called. */
    unsigned int lastTime;

    /** Accumulated time on this timer. */
    unsigned long accumulatedTime;

    /** Timer elapse interval. */
    unsigned int interval;
public:
    AccumulativeTimer();
    AccumulativeTimer(unsigned int t, unsigned int i);

    void reset(unsigned int t);
    void setInterval(unsigned int i);
    bool hasElapsed(unsigned int t);
};

#endif