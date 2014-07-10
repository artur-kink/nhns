#ifndef _EDITOR_
#define	_EDITOR_

#include "Utilities/InputHandler.hpp"
#include "Content/Map.hpp"
#include "Content/MapLoader.hpp"
#include "Objects/RegionManager.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/UI/UI.hpp"

#include "../GameResources.hpp"
#include "SidePanel.hpp"

class Editor{
private:
    InputHandler* input;

    Map* map;

    int mouseTileX;
    int mouseTileY;

    int brushSize;

    bool showTileSelect;

    BaseSprite* drawSprite;

    SidePanel sidePanel;
    Window openWindow;
public:

    UIManager* ui;

    Editor();

    void onEnable();
    void onDisable();

    void update(unsigned int frameTime);
    void draw(RenderTarget& target, unsigned int frameTime);

    void setMap(Map* m);
};

#endif

