#ifndef _CLIENT_
#define	_CLIENT_

#include "EngineCore.hpp"
#include "Graphics/Graphics.hpp"
#include "Content/Map.hpp"
#include "Graphics/UI/UIManager.hpp"
#include "Utilities/Utilities.hpp"
#include "Networking/Networking.hpp"
#include "Objects/EntityManager.hpp"

#include "GameResources.hpp"
#include "Editor/Editor.hpp"
#include "Entities/Entity.hpp"

class Client:public EngineCore{
private:

    /** Game time on server. */
    unsigned int serverTime;
    Timer serverTimer;
    
    NetworkHandler network;
    bool connected;

    Timer pingTimer;
    Timer lastMessage;

    /** Main camera. */
    Camera camera;

    IntervalCounter fpsCounter;
    Label fpsLabel;

    UIManager ui;

    Map* map;

    Entity* player;
    EntityManager entities;

    byte clientId;

    bool debug;
    Editor editor;

protected:

#ifdef _PC_
    virtual void sfmlEvent(sf::Event event);
#endif

public:
    
    Client();

    void connect(const char* addr, unsigned short port);

    virtual void update(unsigned int frameTime);
    virtual void draw(unsigned int frameTime);

    void setServerTime(unsigned int time);
    unsigned int getServerTime();

    ~Client();
};

#endif
