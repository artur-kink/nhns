#ifndef _TIMEDTWEEN_
#define _TIMEDTWEEN_

#include "BaseTween.hpp"


/**
 * A tween class based on delta time.
 */
template <class T> class TimedTween:public BaseTween<T>{
protected:
    unsigned int tweenLength;

public:
    TimedTween(){

    }

    virtual void start(T* target, T value, unsigned int length, unsigned int frameTime){
        if(length == 0)
            return;

        BaseTween<T>::start(target, value, frameTime);
        tweenLength = length;
    }

    virtual void update(unsigned int frameTime){
        if(!BaseTween<T>::active)
            return;

        (*BaseTween<T>::tweenTarget) = ((T)(frameTime - BaseTween<T>::startTime)/tweenLength)*(BaseTween<T>::tweenTargetValue - BaseTween<T>::tweenStartValue) + BaseTween<T>::tweenStartValue;
        if(frameTime >= BaseTween<T>::startTime + tweenLength){
            (*BaseTween<T>::tweenTarget) = BaseTween<T>::tweenTargetValue;
            BaseTween<T>::stop();
        }
    }
};

#endif
