#include <SFML/Window/Keyboard.hpp>

#include "Editor.hpp"
#include "Content/MapLoader.hpp"

Editor::Editor(){
    input = InputHandler::I();

    brushSize = 1;
    showTileSelect = false;
    drawSprite = 0;

    openWindow.setTitle("Open Map");
}

/**
 * Called when editor is enabled.
 */
void Editor::onEnable(){
    if(drawSprite == 0){
        drawSprite = Resources->sprites.sprites[0];
    }
    ui->addElement(&sidePanel);
}

/**
 * Called when editor is disabled.
 */
void Editor::onDisable(){
    ui->removeElement(&sidePanel);
}

void Editor::update(unsigned int frameTime){
    
    mouseTileX = input->getPointer(InputHandler::i_Mouse, 0)/TILESIZE;
    mouseTileY = input->getPointer(InputHandler::i_Mouse, 1)/TILESIZE;

    if(input->isButtonReleased(1, sf::Mouse::Left)){
        if(showTileSelect){
            if(mouseTileX + mouseTileY < Resources->sprites.spriteCount){
                drawSprite = Resources->sprites.sprites[mouseTileX + mouseTileY];
                showTileSelect = false;
            }
        }
    }

    if(ui->hoverElement == 0){
        if(input->isButtonDown(1, sf::Mouse::Left)){
            if(!showTileSelect){
                if(input->isButtonDown(0, sf::Keyboard::B)){
                    for(int r = 0; r < brushSize; r++){
                        for(int c = 0; c < brushSize; c++){
                            if(mouseTileX + c >=  0 && mouseTileX + c < map->width &&
                                mouseTileY + r >= 0 && mouseTileY + r < map->height)
                                map->getTile(mouseTileX + c, mouseTileY + r).properties = 1;
                        }
                    }
                }else{
                    //Add sprite to tile map.
                    for(int r = 0; r < brushSize; r++){
                        for(int c = 0; c < brushSize; c++){
                            if(mouseTileX + c >=  0 && mouseTileX + c < map->width &&
                                mouseTileY + r >= 0 && mouseTileY + r < map->height)
                                map->getTile(mouseTileX + c, mouseTileY + r).layers[0] = drawSprite->index;
                        }
                    }
                }
            }
        }else if(input->isButtonDown(1, 2)){
            if(!showTileSelect){
                if(input->isButtonDown(0, sf::Keyboard::B)){
                    for(int r = 0; r < brushSize; r++){
                        for(int c = 0; c < brushSize; c++){
                            if(mouseTileX + c >=  0 && mouseTileX + c < map->width &&
                                mouseTileY + r >= 0 && mouseTileY + r < map->height)
                                map->getTile(mouseTileX + c, mouseTileY + r).properties = 0;
                        }
                    }
                }else{
                    //Clear tiles.
                    for(int r = 0; r < brushSize; r++){
                        for(int c = 0; c < brushSize; c++){
                            if(mouseTileX + c >=  0 && mouseTileX + c < map->width &&
                                mouseTileY + r >= 0 && mouseTileY + r < map->height)
                                map->getTile(mouseTileX + c, mouseTileY + r).layers[0] = NO_SPRITE;
                        }
                    }
                }
            }
        }
    }

    if(!ui->hasKeyboard){
        if(input->isButtonPressed(0, sf::Keyboard::T)){
            showTileSelect = !showTileSelect;
        }

        if(input->isButtonPressed(0, sf::Keyboard::O)){
            ui->addElement(&openWindow);
        }

        if(input->isButtonPressed(0, sf::Keyboard::Return)){
            MapLoader::saveRawMap(map, &Resources->sprites, new RegionManager());
        }

        if(input->isButtonPressed(0, sf::Keyboard::Add)){
            brushSize++;
        }
        if(input->isButtonPressed(0, sf::Keyboard::Subtract)){
            brushSize--;
            if(brushSize < 1)
                brushSize = 1;
        }
    }
}

void Editor::draw(RenderTarget& target, unsigned int frameTime){

    //Draw current brush.
    for(int r = 0; r < brushSize; r++){
        for(int c = 0; c < brushSize; c++){
            target.draw(drawSprite, (mouseTileX+c)*TILESIZE, (mouseTileY+r)*TILESIZE);
        }
    }
    
    //Draw tile selection screen.
    if(showTileSelect){
        RenderObject obj;
        Color bg;
        bg.r = bg.g = bg.b = 0.3;
        bg.a = 0.75;
        target.drawRect(obj, target.width, target.height, bg);
        
        int drawX = 0;
        for(unsigned short i = 0; i < Resources->sprites.spriteCount; i++){
            BaseSprite* sprite = Resources->sprites.sprites[i];
            
            target.draw(sprite, drawX, 0);

            drawX += sprite->width;
        }
    }
}

void Editor::setMap(Map* m){
    map = m;
}