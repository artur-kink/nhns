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

    Log << LC_E << LL_I << "Client initialized.";
}

void Client::connect(const char* addr, unsigned short port){

    Log << LL_D << LC_N << "Connecting to " << addr << ":" << port;

    network.bind(50012);
    network.setOutConnection(addr, port);
    network.addMessage(Message::m_c_ConnectionRequest, 0);
    network.forceSendMessages();
    connected = true;
}

void Client::update(unsigned int frameTime){
    Resources->frameTime = frameTime;

    //Handle network messages.
    if(connected){
        MessageQueue* messages = network.getMessages();
        if(messages){
            Log << LL_D << LC_N << "Got network messages.";
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

    graphics.draw(Resources->sprites.getSprite("character"), 0, 0);

    if(debug){
        editor.draw(graphics, frameTime);
    }

    fpsCounter.increment(frameTime);
    fpsLabel.setString(StringHelper::itos(fpsCounter.getCounter()));

    ui.draw(&graphics);
}

Client::~Client(){
    Log << LC_E << LL_I << "Uninitializing Client";
    delete Resources;
    ui.clear();
    graphics.cleanup();
    
    Log << LC_E << LL_I << "Terminating Loggers";
    Log.close();
}