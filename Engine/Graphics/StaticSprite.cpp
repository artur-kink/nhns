#include "StaticSprite.hpp"

StaticSprite::StaticSprite(){
    
}

#ifdef _PC_
/** 
* Create static sprite with provided texture.
*/
StaticSprite::StaticSprite(int spriteSheet, int spriteIndex, const sf::Texture& texture, int x, int y, int w, int h){
    type = BaseSprite::st_Static;
    sheet = spriteSheet;
    index = spriteIndex;
    drawSprite.setTexture(texture);
    drawSprite.setTextureRect(sf::IntRect(x, y, w, h));
    width = w;
    height = h;
    this->x = x;
    this->y = y;
    name = 0;
}
#endif

/** 
* Create static sprite without specified texture.
*/
StaticSprite::StaticSprite(int spriteSheet, int spriteIndex, int x, int y, int w, int h){
    sheet = spriteSheet;
    index = spriteIndex;
#ifdef _PC_
    drawSprite = sf::Sprite();
    drawSprite.setTextureRect(sf::IntRect(x, y, w, h));
#endif
    this->x = x;
    this->y = y;
    width = w;
    height = h;
    name = 0;
}


#ifdef _PC_
/** 
* Get SFML Sprite representation.
*/
sf::Sprite StaticSprite::getSprite(){
    return drawSprite;
}



#endif

void StaticSprite::draw(BaseRenderTarget* target, RenderObject& obj) const{

#ifdef _PC_
    obj.sourceHeight = height;
    obj.sourceWidth = width;
    obj.sprite = drawSprite;
#endif

    for(byte i = 0; i < transformationCounter; i++)
        transformations[i]->apply(obj);

    target->draw(obj);
}

#ifdef _PC_
/**
 * Write StaticSprite info to stream.
 */
void StaticSprite::serialize(std::ofstream& destination){
    unsigned char type = 0;
    destination.write((char*) &type, sizeof(type));
    destination.write((char*) &sheet, sizeof(sheet));
    destination.write((char*) &getSprite().getTextureRect().left, sizeof(getSprite().getTextureRect().left));
    destination.write((char*) &getSprite().getTextureRect().top, sizeof(getSprite().getTextureRect().top));
    destination.write((char*) &getSprite().getTextureRect().width, sizeof(getSprite().getTextureRect().width));
    destination.write((char*) &getSprite().getTextureRect().height, sizeof(getSprite().getTextureRect().height));
}
#endif

void StaticSprite::deserialize(MemoryPool* source){
    source->read((char*) &sheet, sizeof(sheet));
    source->read((char*) &x, sizeof(x));
    source->read((char*) &y, sizeof(y));
    source->read((char*) &width, sizeof(width));
    source->read((char*) &height, sizeof(height));
#ifdef _PC_
    drawSprite.setTextureRect(sf::IntRect(x, y, width, height));
#endif
}

/** 
* Doesn't delete anything. Name and texture references should be deleted
* by SpriteManager.
*/
StaticSprite::~StaticSprite(){
}