#include "MathHelper.hpp"

/**
 * Initialize math helper.
 * Call once at beginning of program.
 */
void MathHelper::init(){
    srand(time(0));
}

/**
 * Get absolute value of float.
 * @param val Signed float value.
 * @return Absolute float value.
 */
float MathHelper::abs(float val){
    return std::abs(val);
}

/**
 * Get absolute value of integer.
 * @param val Signed integer value.
 * @return Absolute integer value.
 */
int MathHelper::abs(int val){
    return std::abs(val);
}

/**
 * Get random positive integer.
 */
unsigned int MathHelper::rand(){
    return std::rand();
}

/**
 * Get random positive integer between [0 and max).
 * @param max Maximum value of random integer.
 */
unsigned int MathHelper::rand(unsigned int max){
    return rand(0, max);
}

/**
 * Get random positive integer between min and max. [min, max)
 * Warning: Will not work if max + min = 0;
 * @param min Minimum value of random integer, inclusive.
 * @param max Maximum value of random integer, exclusive.
 */
unsigned int MathHelper::rand(int min, int max){
    unsigned int rand = std::rand() % (max + min);
    if(rand > max)
        return rand - min;
    return  rand;
}

/**
 * Get random double between 0 and 1.
 */
double MathHelper::randDouble(){
    return ((double)std::rand())/((double)RAND_MAX);
}

/**
 * Get random float between 0 and 1.
 */
float MathHelper::randFloat(){
    return ((float)std::rand())/((float)RAND_MAX);
}

/**
 * Get random float between 0 and max. [0, max)
 * @param max Maximum value of random float, exclusive.
 */
float MathHelper::randFloat(float max){
    return (randFloat())*max;
}

/**
 * Get random float between min and max. [min, max)
 * @param min Minimum vaue of random foat, inclusive.
 * @param max Maximum value of random float, exclusive.
 */
float MathHelper::randFloat(float min, float max){
    return min + randFloat(max - min);
}