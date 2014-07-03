#include "Server.hpp"

/** 
 * Initializes a new instance of the Server class.
 */
Server::Server(){
    StringHelper::init();
    MathHelper::init();

    char *filename = new char[64];
    filename[0] = 0;
    DateTime dt = CalendarTime::getDateTime();
    strcpy(filename, "Log/server_");
    strcat(filename, StringHelper::ustos(dt.month));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.day));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.hour));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.minute));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.second));
    strcat(filename, ".txt");

    FileLogger* fileLogger = new FileLogger(filename, ';');
    delete filename;

    fileLogger->setLevelFilter(Logger::ll_Debug);
    fileLogger->lockFilter();
    Log >> new ConsoleLogger() >> fileLogger;
    Log.setLevelFilter(Logger::ll_Debug);

    Log << LL_D << LC_E << "Initializing server.";

    numClients = 0;
    maxClients = 10;
    timeout = 1000;
    clients = new Client[maxClients];
}

/**
 * 
 */
void Server::start(){

    Log << LL_D << LC_E << "Starting server.";
    running = true;
    
    Time currentTime;
    AccumulativeTimer updateTimer;
    updateTimer.setInterval(25000);
    updateTimer.reset(currentTime.getTimeMicroseconds());

    Log << LL_D << LC_N << "Listening for connections.";
    connectionListener.bind(50013);
    while(running){

        //Handle network messages.
        MessageQueue* messages = connectionListener.getMessages();
        if(messages){
            Log << LL_D << LC_N << "Received " << messages->size << " messages from "
                << connectionListener.lastMessageAddress << ":" << connectionListener.lastMessagePort;

            MessageIterator message = messages->begin();
            switch((*message)->group){
                case Message::g_Normal:
                    handleMessages(message);
                    break;
                case Message::g_Critical:
                    handleMessages(message);
                    break;
                case Message::g_NewConnection:
                    handleNewConnection(message);
                    break;
                case Message::g_Loading:
                    handleLoadingConnection(message);
                    break;
            }
        }
        handleTimeouts();

        //Run server update in a semi fixed step format.
        while(updateTimer.hasElapsed(currentTime.getTimeMicroseconds())){
            unsigned int frameTime = currentTime.getTimeMilliseconds();
            Log << LL_V << LC_E << "Running Update";
            update(frameTime);
        }
    }
}

void Server::update(unsigned long frameTime){
    
}

void Server::stop(){

}

void Server::handleMessages(MessageIterator& message){
    //Find message client.
    int sourceClient = -1;
    for(int i = 0; i < maxClients; i++){
        if(clients[i].status == Client::cs_Connected &&
            strcmp(clients[i].network.getOutAddress(), connectionListener.lastMessageAddress) == 0 &&
            clients[i].network.getOutPort() == connectionListener.lastMessagePort){
            sourceClient = i;
            break;
        }
    }

    if(sourceClient == -1){
        Log << LL_W << LC_N << "Invalid message source "
            << connectionListener.lastMessageAddress << ":" << connectionListener.lastMessagePort;
        return;
    }

    clients[sourceClient].timeoutTimer.reset(Time::getInstance()->getTimeMilliseconds());
    for(message; *message; ++message){
        switch((*message)->code){
            case Message::m_b_Ping:
                clients[sourceClient].network.addMessage(Message::m_b_Ping, 0);
                clients[sourceClient].network.forceSendMessages();
                break;
            case Message::m_b_ConnectionTerminate:
                Log << LL_I << LC_N << "Client terminated connection.";
                clients[sourceClient].status = Client::cs_Disconnected;
                break;
        }
    }

}

/**
* Handles connections that have been accepted by the server but not yet added to the clients list.
* The server is waiting for these connections to notify that they are ready to be added to the game world.
*/
void Server::handleLoadingConnection(MessageIterator& message){

    //Find client thats connecting.
    int loadingClient = -1;
    for(int i = 0; i < maxClients; i++){
        if(clients[i].status == Client::cs_Connecting &&
            strcmp(clients[i].network.getOutAddress(), connectionListener.lastMessageAddress) == 0 &&
            clients[i].network.getOutPort() == connectionListener.lastMessagePort){
            loadingClient = i;
            break;
        }
    }

    //Message did not come from a valid loading client.
    if(loadingClient == -1){
        Log << LL_W << LC_N << "Invalid loading message from "
            << connectionListener.lastMessageAddress << ":" << connectionListener.lastMessagePort;
        
        return;
    }

    if((*message)->code == Message::m_c_ClockSyncReq){
        uint32_t time = Time::getInstance()->getTimeMilliseconds();
        clients[loadingClient].network.addMessage(Message::m_s_ClockSyncResp, &time);
        clients[loadingClient].timeoutTimer.reset(Time::getInstance()->getTimeMilliseconds());
        clients[loadingClient].network.forceSendMessages();
        
        Log << LL_D << LC_N << "Clock sync request";
    }else if((*message)->code == Message::m_c_ConnectionComplete){
        Log << LL_D << LC_N << "Client loading complete.";
        clients[loadingClient].status = Client::cs_Connected;
    }
}

/**
* Handles incoming connection requests.
* If the server accepts the incoming connection, an accept message is sent to the client.
* The client is added to the loading list.
*/
void Server::handleNewConnection(MessageIterator& message){

    Log << LL_D << LC_N << "Connection request from " << connectionListener.lastMessageAddress << ":" << connectionListener.lastMessagePort;
    connectionListener.setOutConnection(connectionListener.lastMessageAddress, connectionListener.lastMessagePort);
    if((*message)->code == Message::m_c_ConnectionRequest && numClients < maxClients){

        //Send accept information
        connectionListener.addMessage(Message::m_s_ConnectionAccept, 0);

        //If accept message was successfully sent, add connection to loading client list.
        if(connectionListener.forceSendMessages()){
            //Find available client to place connection into.
            for(int i = 0; i < maxClients; i++){
                if(clients[i].status == Client::cs_Disconnected){

                    Log << LL_D << LC_N << "New client added.";
                    clients[i].status = Client::cs_Connecting;
                    clients[i].timeoutTimer.reset(Time::getInstance()->getTimeMilliseconds());
                    clients[i].network.setOutConnection(connectionListener.lastMessageAddress, connectionListener.lastMessagePort);
                    numClients++;
                    break;
                }
            }
            return;
        }
    }

    //If we reached here then either server is full or connection request
    //was rejected. Send reject message
	connectionListener.addMessage(Message::m_s_ConnectionRefuse, 0);
    connectionListener.forceSendMessages();
}

/**
 * Removes clients that have timed out.
 */
void Server::handleTimeouts(){

    unsigned int currentTime = Time::getInstance()->getTimeMilliseconds();
    for(int i = 0; i < maxClients; i++){
        if(clients[i].status != Client::cs_Disconnected){
            
            //If client has timed out remove client from game.
            if(clients[i].timeoutTimer.hasElapsed(currentTime, timeout)){
                Log << LL_D << LC_N << "Client timed out.";
                clients[i].network.addMessage(Message::m_b_ConnectionTerminate, 0);
                clients[i].network.forceSendMessages();
                clients[i].status = Client::cs_Disconnected;
                numClients--;
            }
        }
    }
}