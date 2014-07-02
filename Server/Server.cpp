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
            Log << LL_D << LC_N << "Received " << messages->size << " messages.";

            MessageIterator message = messages->begin();
            switch((*message)->group){
                case Message::g_Normal:
                    break;
                case Message::g_Critical:
                    break;
                case Message::g_NewConnection:
                    handleNewConnection(message);
                    break;
                case Message::g_Loading:
                    break;
            }
        }

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


/**
* Handles connections that have been accepted by the server but not yet added to the clients list.
* The server is waiting for these connections to notify that they are ready to be added to the game world.
*/
void Server::handleLoadingConnection(MessageIterator& message){

    /*
    LoadingClientCollection::LoadingClientNode* loadingClient = loadingClientsList.clientList;

    //While loop to find the corresponding client
    while(loadingClient != 0){
        LoadingClientCollection::LoadingClientNode* nextClient = loadingClient->next;

        if(loadingClient->address->toInteger() == address.toInteger()){

            if((*iMessage)->code == Message::m_c_ClockSyncReq){
				uint32_t time = MessageQueue::serverTime->getTime();
				globalOutQueue.createMessage(Message::m_s_ClockSyncResp, &time);
                loadingClient->timeout->restart();
                globalOutQueue.forceSendQueue(socket, *loadingClient->address, loadingClient->port);
                globalOutQueue.clearQueue();
                cout << "Clock sync request" << endl;
            }else if((*iMessage)->code == Message::m_c_LoadingComplete){
                //Client connected add to game
                Client* addClient = clientsList.addClient();
				playerManager.createPlayer(&addClient->entity);
				addClient->setup(loadingClient->address->toString(), *loadingClient->address, loadingClient->port);
                addClient->entity.region = regionManager.createRegion("player");

                loadingClientsList.removeClient(loadingClient);
                sEngine.clientConnected(addClient);

                //Send client add reply
				globalOutQueue.createMessage(Message::m_s_ClientAdd, &addClient->index);

                //Send client game state
                Packet_GameState state;
                state.maxClients = clientsList.MAX_CLIENTS;
				globalOutQueue.createMessage(Message::m_s_GameState, &state);

                //Send client all client states.
                int clientCounter = 0;
				for(int i = 0; i < clientsList.MAX_CLIENTS; i++){
					if(clientsList[i]->active){
						Packet_ClientState clientState = PacketHelper::ClientState(&clientsList[i]->entity, clientsList[i]->name.c_str());
						globalOutQueue.createMessage(Message::m_s_NewClient, &clientState);

                        if(clientCounter == addClient->index){
                            networkHandler.sendAllMessageExcept(Message::m_s_NewClient, &clientState, addClient->index);
                        }
						clientCounter++;
					}
                }

				//Send client all entity states
				for(int i = 0; i < entityManager.size; i++){
					if(entityManager.entities[i] != 0){
						Packet_EntityState entityState = PacketHelper::EntityState(entityManager.entities[i]);
						globalOutQueue.createMessage(Message::m_s_NewEntity, &entityState);
					}
				}

                globalOutQueue.forceSendQueue(socket, addClient->address, addClient->port);
                globalOutQueue.clearQueue();
                addClient->lastMessage.restart();
            }

            return;
        }
        loadingClient = nextClient;
    }
    */
}

/**
* Handles incoming connection requests.
* If the server accepts the incoming connection, an accept message is sent to the client.
* The client is added to the loading list.
*/
void Server::handleNewConnection(MessageIterator& message){

    connectionListener.setOutConnection(connectionListener.lastMessageAddress, connectionListener.lastMessagePort);
    if((*message)->code == Message::m_c_ConnectionRequest && numClients < maxClients){

        //Send accept information
        connectionListener.addMessage(Message::m_s_ConnectionAccept, 0);

        //If accept message was successfully sent, add connection to loading client list.
        if(connectionListener.forceSendMessages()){
            //Add loading client.
            return;
        }
    }

    //If we reached here then either server is full or connection request
    //was rejected. Send reject message
	connectionListener.addMessage(Message::m_s_ConnectionRefuse, 0);
    connectionListener.forceSendMessages();
}