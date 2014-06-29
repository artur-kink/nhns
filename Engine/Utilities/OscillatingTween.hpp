#ifndef _OSCILLATINGTWEEN_
#define _OSCILLATINGTWEEN_

#include "BaseTween.hpp"

/**
 * Oscillating inbetween. Oscillates between
 * two given values by time. The oscillating tween
 * does not stop unless stop is called.
 */
template <class T> class OscillatingTween:public BaseTween<T>{
protected:
    unsigned int tweenLength;
    T tweenOscillateValue;
public:
    OscillatingTween(){

    }

    virtual void start(T* target, T value, T value2, unsigned int length, unsigned int frameTime){
        if(length == 0)
            return;

        BaseTween<T>::start(target, value, frameTime);
        tweenOscillateValue = value2;
        tweenLength = length;
    }

    virtual void update(unsigned int frameTime){
        if(!BaseTween<T>::active)
            return;

        (*BaseTween<T>::tweenTarget) = ((T)(frameTime - BaseTween<T>::startTime)/tweenLength)*(BaseTween<T>::tweenTargetValue - BaseTween<T>::tweenStartValue) + BaseTween<T>::tweenStartValue;
        if(frameTime >= BaseTween<T>::startTime + tweenLength){
            (*BaseTween<T>::tweenTarget) = BaseTween<T>::tweenTargetValue;
            start(BaseTween<T>::tweenTarget, tweenOscillateValue, BaseTween<T>::tweenTargetValue, tweenLength, frameTime);
        }
    }
};

#endif
