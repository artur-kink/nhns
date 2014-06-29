#ifndef _SERVER_
#define _SERVER_

#include "Utilities/MathHelper.hpp"
#include "Utilities/Timer.hpp"
#include "Utilities/AccumulativeTimer.hpp"
#include "Utilities/Time.hpp"
#include "Utilities/Logger.hpp"

class Server{
private:
    bool running;

public:
    Server();

    void start();
    void update(unsigned long frameTime);
    void stop();
};

#endif