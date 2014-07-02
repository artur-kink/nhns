#ifndef _CLIENT_
#define	_CLIENT_

#include "EngineCore.hpp"
#include "Graphics/Graphics.hpp"
#include "Content/Map.hpp"
#include "Graphics/UI/UIManager.hpp"
#include "Utilities/Utilities.hpp"
#include "Networking/Networking.hpp"

#include "GameResources.hpp"
#include "Editor.hpp"

class Client:public EngineCore{
private:

    NetworkHandler network;
    bool connected;

    /** Main camera. */
    Camera camera;

    IntervalCounter fpsCounter;
    Label fpsLabel;

    UIManager ui;

    Map* map;

    bool debug;
    Editor editor;
public:
    
    Client();

    void connect(const char* addr, unsigned short port);

    virtual void update(unsigned int frameTime);
    virtual void draw(unsigned int frameTime);

    ~Client();
};

#endif
