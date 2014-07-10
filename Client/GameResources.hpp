#ifndef _GAMERESOURCES_
#define _GAMERESOURCES_

#include "Audio/AudioManager.hpp"
#include "Graphics/SpriteManager.hpp"
#include "Graphics/ShaderManager.hpp"

#define Resources GameResources::I()

class GameResources{
private:
    static GameResources* instance;
public:
    unsigned int frameTime;

    AudioManager audio;
    SpriteManager sprites;
    ShaderManager shaders;

    SpriteManager editorSprites;

    GameResources();
    ~GameResources();

    static GameResources* I();
};


#endif