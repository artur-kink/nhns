#include "Client.hpp"

Client::Client(){
    FileLogger* fileLogger = new FileLogger("debug", ';');
    fileLogger->setLevelFilter(Logger::ll_Debug);
    fileLogger->lockFilter();
    Log >> new ConsoleLogger() >> fileLogger;
    Log.setLevelFilter(Logger::ll_Debug);

    Log << LC_E << LL_I << "Initializing client.";

    camera.setSize(1024, 576);
    camera.setScreenSize(1280, 720);
    camera.setPosition(0, 0);
    
    graphics.setSize(1280, 720);

    FontHandler* font = new FontHandler();
    font->loadFont("arial");
    font->setFontSize(10);
    font->setFontColor(Color::White);
    graphics.setFont(font);

    fpsCounter.setInterval(1000);

    //Initialize UI.
    ui.setSize(1280, 720);

    Log << LC_E << LL_I << "Client initialized.";
}


void Client::update(unsigned int frameTime){
    Resources->frameTime = frameTime;
    
    //Update sprites.
    Resources->sprites.update(frameTime);

    //Update UI.
    ui.update(frameTime, 0, 0, false, false);

    //Update camera state.
    //Since drawing occurs more often
    //than game update, we update camera here.
    camera.update(frameTime);
}

void Client::draw(unsigned int frameTime){
    graphics.setCamera(&camera);
    
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