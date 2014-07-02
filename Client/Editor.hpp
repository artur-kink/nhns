#ifndef _EDITOR_
#define	_EDITOR_

#include "Utilities/InputHandler.hpp"
#include "Content/Map.hpp"
#include "Graphics/Graphics.hpp"

#include "GameResources.hpp"


class Editor{
private:
    InputHandler* input;

    Map* map;

    int mouseTileX;
    int mouseTileY;

    int brushSize;

    bool showTileSelect;

    BaseSprite* drawSprite;
public:
    Editor();

    void onEnable();

    void update(unsigned int frameTime);
    void draw(RenderTarget& target, unsigned int frameTime);

    void setMap(Map* m);
};

#endif

