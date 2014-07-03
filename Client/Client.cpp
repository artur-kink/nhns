#include "Client.hpp"

Client::Client(){

    char *filename = new char[64];
    filename[0] = 0;
    DateTime dt = CalendarTime::getDateTime();
    strcpy(filename, "Log/debug_");
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

    Log << LC_E << LL_I << "Initializing client.";
    Resources->sprites.load("sprites.dat");

    camera.setSize(1280, 720);
    camera.setScreenSize(1280, 720);
    camera.setPosition(0, 0);
    
    graphics.setSize(1280, 720);

    FontHandler* font = new FontHandler();
    font->loadFont("arial.ttf");
    font->setFontSize(10);
    font->setFontColor(Color::White);
    graphics.setFont(font);

    fpsCounter.setInterval(1000);
    fpsLabel.setPosition(0, 0);

    //Initialize UI.
    ui.setSize(1280, 720);

    ui.addElement(&fpsLabel);

    map = new Map("empty", 1280/8, 720/8);
    editor.setMap(map);

    debug = false;
    connected = false;

    Log << LC_E << LL_I << "Client initialized.";
}

unsigned int Client::getServerTime(){
    return serverTime + serverTimer.getElapsedTime(Time::getInstance()->getTimeMilliseconds());
}

void Client::setServerTime(unsigned int time){
    serverTime = time;
    serverTimer.reset(Time::getInstance()->getTimeMilliseconds());
}

void Client::connect(const char* addr, unsigned short port){

    Log << LL_I << LC_N << "Connecting to " << addr << ":" << port;

    //Disconnect if connected.
    connected = false;
    network.close();

    network.bind(50012);
    network.setOutConnection(addr, port);
    network.addMessage(Message::m_c_ConnectionRequest, 0);
    network.forceSendMessages();
    MessageQueue* response = network.getMessagesBlocking(1000);
    if(response == 0 ||  *response->getFirstMessage(Message::m_s_ConnectionAccept) == 0){
        Log << LL_I << LC_N << "Connection request denied or timed out.";
        return;
    }else{
        Log << LL_I << LC_N << "Connection request accepted.";
    }

    //Sync client time with server.
    Log << LL_I << LC_N << "Synchronizing clock with server.";
    int syncCounter = 0;
    uint32_t previousOffset = 0;
    setServerTime(0);
    while(true){
        //Send clock sync request.
		network.addMessage(Message::m_c_ClockSyncReq, 0);
        uint32_t requestTime = getServerTime();
        Log << LL_I << LC_N << "Request Time: " << requestTime;
        network.forceSendMessages();

        //Get request response.
        response = network.getMessagesBlocking(1000);
        if(!response){
            Log << LL_I << LC_N << "Clock sync timed out.";
            return;
        }

        MessageIterator message = response->getFirstMessage(Message::m_s_ClockSyncResp);
        if((*message)){

            uint32_t receivedServerTime = *(uint32_t*)(*message)->buffer;
            uint32_t responseTime = getServerTime();
            uint32_t offset = ((receivedServerTime - requestTime) + (receivedServerTime - responseTime))/2;
            Log << LL_I << LC_N << "Server Time: " << receivedServerTime << ", Response Time: " << responseTime
                << ", Offset: " << offset;

            if(abs((long int)previousOffset) > abs((long int)offset) || syncCounter == 0){
                previousOffset = offset;
                serverTime = serverTime + offset;
            }
            if(offset == 0 || syncCounter >= 5)
                break;
            syncCounter++;
        }
    }

    //Notify server that we are ready to join game.
	network.addMessage(Message::m_c_ConnectionComplete, 0);
    network.forceSendMessages();

    connected = true;
    lastMessage.setInterval(500);
    lastMessage.reset(Time::getInstance()->getTimeMilliseconds());
}

void Client::update(unsigned int frameTime){
    Resources->frameTime = frameTime;

    //Handle network messages.
    if(connected){
        MessageQueue* messages = network.getMessages();
        if(messages){
            Log << LL_D << LC_N << "Received " << messages->size << " network message(s).";

            for(MessageIterator& message = messages->begin(); *message; ++message){
                switch((*message)->code){
                    case Message::m_b_Ping:
                        Log << LL_D << LC_N << "Ping " << pingTimer.getElapsedTime(frameTime) << "ms.";
                        break;
                }
            }
        }

        if(lastMessage.hasElapsed(frameTime)){
            network.addMessage(Message::m_b_Ping, 0);
            pingTimer.reset(frameTime);
        }
    }
    
    //Update sprites.
    Resources->sprites.update(frameTime);

    //Update UI.
    ui.update(frameTime, 0, 0, false, false);

    //Update camera state.
    //Since drawing occurs more often
    //than game update, we update camera here.
    camera.update(frameTime);

#ifdef _PC_
    byte currentDir = player.dir;
    if(input.isButtonDown(0, sf::Keyboard::W)){
        player.dir = Entity::dir_Up;
    }else if(input.isButtonDown(0, sf::Keyboard::S)){
        player.dir = Entity::dir_Down;
    }else{
        player.dir = Entity::dir_None;
    }

    
    if(input.isButtonDown(0, sf::Keyboard::A)){
        player.dir |= Entity::dir_Right;
    }else if(input.isButtonDown(0, sf::Keyboard::D)){
        player.dir |= Entity::dir_Left;
    }

    if(connected && currentDir != player.dir){
        network.addMessage(Message::m_c_PlayerMove, &player.dir);
    }

    if(input.isButtonPressed(0, sf::Keyboard::C)){
        connect("localhost", 50013);
    }

    if(input.isButtonDown(0, sf::Keyboard::Escape)){
        stop();
    }

    if(input.isButtonPressed(0, sf::Keyboard::Tab)){
        debug = !debug;
        if(debug){
            editor.onEnable();
        }
    }

    if(debug){
        editor.update(frameTime);
    }
#endif

    player.update(frameTime);

    if(connected){
        network.sendMessages();
    }
}

void Client::draw(unsigned int frameTime){
    graphics.setCamera(&camera);

    graphics.clear(0, 0, 0);

    //Draw map
    for(int l = 0; l < 5; l++){
        for(int r = 0; r < map->height; r++){
            for(int c = -3; c < camera.width/TILESIZE+2; c++){
                int col = camera.x/TILESIZE - 1 + c;
                int colPos = col*TILESIZE;
                if(col >= map->width){
                    col -= map->width;
                }else if(col < 0){
                    col += map->width;
                }
                if(map->getTile(col, r).layers[l] != NO_SPRITE){
                    graphics.draw(Resources->sprites.getSprite(map->getTile(col, r).layers[l]), colPos, r*TILESIZE);
                }
            }
        }
    }

    player.draw(graphics, frameTime);
    
    if(debug){
        editor.draw(graphics, frameTime);
    }

    fpsCounter.increment(frameTime);
    fpsLabel.setString(StringHelper::itos(fpsCounter.getCounter()));

    ui.draw(&graphics);
}

Client::~Client(){
    Log << LC_E << LL_I << "Uninitializing Client";
    if(connected){
        Log << LC_N << LL_I << "Sending disconnect message";
        network.addMessage(Message::m_b_ConnectionTerminate, 0);
        network.forceSendMessages();
        network.close();
    }
    delete Resources;
    ui.clear();
    
    Log << LC_E << LL_I << "Terminating Loggers";
    Log.close();
}