#ifndef _SPRITEMANAGER_
#define _SPRITEMANAGER_

#ifdef _PC_
#include "SFML/Graphics.hpp"
#endif

#include <vector>
#include <string>

#include "Utilities/ResourceManager.hpp"
#include "Utilities/StringHelper.hpp"
#include "Utilities/KeyValuePair.hpp"

#include "MatrixTransformation.hpp"

#include "StaticSprite.hpp"
#include "AnimatedSprite.hpp"
#include "LayeredSprite.hpp"
#include "SpriteSet.hpp"

/** 
* This class is used to load, access and manage sprites specified in sprite .dat files.
*/
class SpriteManager:public ResourceManager{
    friend class SpriteLoader;
private:

    /** 
    * This list contains all sprites that can be updated.
    */
    std::vector<DynamicSprite*> dynamicList;
    
public:
    /** 
    * The loaded sprites.
    */
    BaseSprite** sprites;

    /** 
    * Index of sprite names;
    */
    KeyValuePair<BaseSprite>* spriteNames;

    /** 
    * Number of sprites.
    */
    unsigned short spriteCount;

    /** 
    * Sprite sets.
    */
    SpriteSet** spriteSets;

    /** 
    * Index of sprite set names;
    */
    KeyValuePair<SpriteSet>* spriteSetNames;
    
    /** 
    * Number of sprites.
    */
    unsigned short spriteSetCount;

#ifdef _PC_
    /** 
    * Textures used by sprites.
    */
    sf::Texture* textures;
#endif
    char** textureNames;

#ifdef _PC_
    /** 
    * Textures encapsulated in SFML sprites.
    */
    sf::Sprite* textureSprites;
#endif

    /** 
    * Number of sprite sheets.
    */
    byte sheetCount;

    /**
     * Array of transformations.
     */
    BaseTransformation** transformations;

    /**
     * Number of transformations.
     */
    unsigned short transformationCount;

    /**
     * Transformation names
     */
    char** transformationNames;
    
    SpriteManager();

    void addDynamicSprite(DynamicSprite* sprite);
    void removeDynamicSprite(DynamicSprite* sprite);

    BaseSprite* getSprite(unsigned short index);
    unsigned short getSpriteIndex(const char* name);
    BaseSprite* getSprite(const char* name);
    void deleteSprite(BaseSprite* sprite);

    SpriteSet* getSpriteSet(const char* name);

    void update(unsigned int time);

    virtual void load(const char* path);
#ifdef _PC_
    static void getSpriteTransformations(pugi::xml_node node, BaseSprite* sprite, std::vector<char*>& transformNames, std::vector<BaseTransformation*>& transforms);
    static void parseTransformation(pugi::xml_node node, std::vector<char*>& transformNames, std::vector<BaseTransformation*>& transforms);
    static int getStringIndex(std::vector<char*>* strings, const char* name);
    
    virtual void loadRaw(const char* file);
    virtual void save(const char* file);
#endif

    ~SpriteManager();
};

#endif