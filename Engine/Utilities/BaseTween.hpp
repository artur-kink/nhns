#ifndef _BASETWEEN_
#define _BASETWEEN_

/**
 * Base class for inbetweening values.
 */
template <class T> class BaseTween{
protected:
    /** Time the tween was started. */
    unsigned int startTime;

    /** Value that tween target began at. */
    T tweenStartValue;

    

    /** Pointer to the value being tweened. */
    T* tweenTarget;

public:
    /** Target value to reach in tween. */
    T tweenTargetValue;

    /** Whether the tween is actively running. */
    bool active;

    BaseTween(){
        active = false;
    }

    virtual void start(T* target, T value, unsigned int frameTime){
        if(*target == value)
            return;

        tweenTargetValue = value;
        tweenTarget = target;
        tweenStartValue = *target;

        startTime = frameTime;
        active = true;
    }

    virtual void update(unsigned int frameTime) = 0;

    virtual void stop(){
        active = false;
    }
};

#endif