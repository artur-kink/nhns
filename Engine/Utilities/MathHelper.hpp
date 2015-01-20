#ifndef _MATHHELPER_
#define _MATHHELPER_

#include <cstdlib>
#include <ctime>
#include <cmath>

#define Math MathHelper

/**
 * Helper class for common mathematical functions.
 * Init should be called before this class can be used to setup random seeds.
 */
class MathHelper{
private:

public:
    static void init();

    static float abs(float val);
    static int abs(int val);

    static unsigned int rand();
    static unsigned int rand(unsigned int max);
    static unsigned int rand(int min, int max);

    static double randDouble();

    static float randFloat();
    static float randFloat(float max);
    static float randFloat(float min, float max);
    
    static int max(int a, int b);
    static int min(int a, int b);
};

#endif