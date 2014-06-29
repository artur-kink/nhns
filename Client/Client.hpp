#ifndef _CLIENT_
#define	_CLIENT_

#include "EngineCore.hpp"

#include "Graphics/Graphics.hpp"

#include "GameResources.hpp"

#include "Graphics/UI/UIManager.hpp"

#include "Utilities/Utilities.hpp"

class Client:public EngineCore{
private:
    /** Main camera. */
    Camera camera;
    IntervalCounter fpsCounter;

    UIManager ui;
public:
    
    Client();

    virtual void update(unsigned int frameTime);
    virtual void draw(unsigned int frameTime);

    ~Client();
};

#endif
