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

#include "Client.hpp"

class Server{
private:
    /** Maximum number of clients that can connect to server. */
    int maxClients;
    /** Current number of clients connected to server. */
    int numClients;

    /** Is server running. */
    bool running;

    /** Max time between messages until a client is considered to have timed out. */
    unsigned long timeout;

    NetworkHandler connectionListener;
    Client* clients;
public:
    Server();

    void start();
    void update(unsigned long frameTime);
    void stop();

    void handleMessages(MessageIterator& message);
    void handleNewConnection(MessageIterator& message);
    void handleLoadingConnection(MessageIterator& message);
    void handleTimeouts();
    
};

#endif