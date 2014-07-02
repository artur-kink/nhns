#ifndef _SERVER_
#define _SERVER_

#include "Utilities/MathHelper.hpp"
#include "Utilities/Timer.hpp"
#include "Utilities/AccumulativeTimer.hpp"
#include "Utilities/Time.hpp"
#include "Utilities/Logger.hpp"

#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/FileLogger.hpp"

#include "Networking/Networking.hpp"

class Server{
private:
    int maxClients;
    int numClients;
    
    bool running;

    NetworkHandler connectionListener;
public:
    Server();

    void start();
    void update(unsigned long frameTime);
    void stop();

    void handleNewConnection(MessageIterator& message);
    void handleLoadingConnection(MessageIterator& message);
};

#endif