#include "SpriteManager.hpp"
#include "Utilities/StringHelper.hpp"

SpriteManager::SpriteManager(){

}

/** 
* Gets sprite by sprite index.
*/
BaseSprite* SpriteManager::getSprite(unsigned short index){
    if(index != NO_SPRITE){
        return sprites[index];
    }
    return 0;
}

/** 
* Deletes the specified sprite from memory.
* This is used to clear clear copied sprites.
* @param sprite Sprite to delete.
*/
void SpriteManager::deleteSprite(BaseSprite* sprite){
    if(sprite != 0){
        if(dynamic_cast<DynamicSprite*> (sprite) != 0)
            removeDynamicSprite((DynamicSprite*) sprite);

        delete sprite;
        sprite = 0;
    }
}

/** 
* Updates all dynamic sprites.
*/
void SpriteManager::update(unsigned int time){
    for(unsigned int i = 0; i < dynamicList.size(); i++){
        dynamicList.at(i)->update(time);
    }
}

/** 
* Add a dynamic sprite to the dynamic sprite list.
*/
void SpriteManager::addDynamicSprite(DynamicSprite* sprite){
    dynamicList.push_back(sprite);
}

/** 
* Remove dynamic sprite from the dynamic sprite list.
*/
void SpriteManager::removeDynamicSprite(DynamicSprite* sprite){
    for(unsigned int i = 0; i < dynamicList.size(); i++){
        if(dynamicList.at(i) == sprite){
            dynamicList.erase(dynamicList.begin() + i);
            break;
        }
    }
}

/** 
* Get sprite by name.
*/
BaseSprite* SpriteManager::getSprite(const char* name){
    return KeyValuePair<BaseSprite>::findValue(spriteNames, spriteCount, name);
}

/** 
* Get sprite index in sprite list by name.
*/
unsigned short SpriteManager::getSpriteIndex(const char* name){
    BaseSprite* sprite = KeyValuePair<BaseSprite>::findValue(spriteNames, spriteCount, name);
    if(sprite)
        return sprite->index;
    else
        return NO_SPRITE;
}

/** 
* Get sprite set by name.
*/
SpriteSet* SpriteManager::getSpriteSet(const char* name){
    return KeyValuePair<SpriteSet>::findValue(spriteSetNames, spriteSetCount, name);
}

void SpriteManager::load(const char* path){
    Log << LC_G << LL_D <<"Loading sprite definition file: " << path;
    //Open file
    FileHandler fileHandler;
    MemoryPool* file = fileHandler.readFile(path);
    
    //If file reading succeeded.
    if(file->getBuffer()){

        //Get transformations
        file->read((char*) &transformationCount, sizeof(transformationCount));

        Log << "Transformations Found: " << transformationCount;

        transformations = new BaseTransformation*[transformationCount];
        transformationNames = new char*[transformationCount];
        for(unsigned short i = 0; i < transformationCount; i++){
            //Get transformation name.
            byte nameLength = 0;
            file->read((char*) &nameLength, sizeof(nameLength));
            char* nameChar = new char[nameLength + 1];
            file->readString(nameChar, nameLength);
            nameChar[nameLength] = '\0';
            transformationNames[i] = nameChar;
            //Get type.
            byte type = 0;
            file->read((char*)&type, sizeof(type));
            
            //Get type specific data.
            if(type == BaseTransformation::tt_Matrix){
                MatrixTransformation* transform = new MatrixTransformation(i);
                transformations[i] = transform;
                file->read((char*) &transform->transformFlags, sizeof(transform->transformFlags));

                if(transform->transformFlags & MatrixTransformation::to_Rotate){
                    file->read((char*) &transform->rAngle, sizeof(transform->rAngle));
                    file->read((char*) &transform->rX, sizeof(transform->rX));
                    file->read((char*) &transform->rY, sizeof(transform->rY));
                }

                if(transform->transformFlags & MatrixTransformation::to_Scale){
                    file->read((char*) &transform->sX, sizeof(transform->sX));
                    file->read((char*) &transform->sY, sizeof(transform->sY));
                }

                if(transform->transformFlags & MatrixTransformation::to_Translate){
                    file->read((char*) &transform->tX, sizeof(transform->tX));
                    file->read((char*) &transform->tY, sizeof(transform->tY));
                }
            }
        }

        //Get sprite sheets
        byte numSheets = 0;
        file->read((char*) &numSheets, sizeof(numSheets));

        Log << "Sprites Sheets Found: " << (int)numSheets;
        //Load textures associated with sprite sheets
#ifdef _PC_
        textures = new sf::Texture[numSheets];
        textureSprites = new sf::Sprite[numSheets];
#endif
        textureNames = new char*[numSheets];
        for(byte i = 0; i < numSheets; i++){
            byte sheetNameLength = 0;
            file->read((char*) &sheetNameLength, sizeof(sheetNameLength));
            char* sheetNameChr = new char[sheetNameLength + 1];
            file->readString(sheetNameChr, sheetNameLength);
            char* sheetLoadNameChr = new char[sheetNameLength + 5];
            sheetNameChr[sheetNameLength] = '\0';
            strcpy(sheetLoadNameChr, sheetNameChr);
#ifdef _PC_
            strcat(sheetLoadNameChr, ".tga");
#endif
            sheetLoadNameChr[sheetNameLength + 4] = '\0';
			//Load texure file
#ifdef _PC_
            if(!textures[i].loadFromFile(sheetLoadNameChr))
                continue;

			textureSprites[i].setTexture(textures[i]);
#endif
            textureNames[i] = sheetNameChr;
            Log << "Loaded Sheet: " << sheetNameChr;
        }
        sheetCount = numSheets;

        //Load sprite definitions
        file->read((char*) &spriteCount, sizeof(spriteCount));

        sprites = new BaseSprite*[spriteCount];
        
        Log << "Sprites Found: " << spriteCount;
        for(unsigned short i = 0; i < spriteCount; i++){
            byte spriteType = 0;
            file->read((char*) &spriteType, sizeof(spriteType));
            if(spriteType == 0){ //Static Sprite
                StaticSprite* sprite = new StaticSprite();
                sprite->index = i;
                sprite->deserialize(file);
#ifdef _PC_
                sprite->drawSprite.setTexture(textures[sprite->sheet]);
#endif
                sprites[i] = sprite;
                Log << "Loaded Sprite: " << sprite->sheet << ", " << sprite->x << "x"
                    << sprite->y << ", " << sprite->width << "x" << sprite->height;
            }else if(spriteType == 1){ //Animated Sprite
                AnimatedSprite* sprite = new AnimatedSprite();
                sprite->index = i;
                sprite->deserialize(file);
                //Set frame sprites
                for(int j = 0; j < sprite->frameCount; j++){
                    sprite->frames[j].sprite = getSprite(sprite->frames[j].index);
                }
                sprite->width = sprite->frames[0].sprite->width;
                sprite->height = sprite->frames[0].sprite->height;
                addDynamicSprite(sprite);
                sprites[i] = sprite;
            }else if(spriteType == 2){ //Layered Sprite
                unsigned char layerCount = 0;
                file->read((char*) &layerCount, sizeof(layerCount));
                LayeredSprite* sprite = new LayeredSprite(layerCount, i);
                //Load layered sprite layers
                for(int j = 0; j < spriteType; j++){
                    unsigned short index = 0;
                    file->read((char*) &index, sizeof(index));
                    sprite->layers[j] = getSprite(index);
                }
                sprite->width = sprite->layers[0]->width;
                sprite->height = sprite->layers[0]->height;
                sprites[i] = sprite;
            }
            file->read((char*) &sprites[i]->transformationCounter, sizeof(sprites[i]->transformationCounter));
            for(byte t = 0; t < sprites[i]->transformationCounter; t++){
                unsigned short index = 0;
                file->read((char*) &index, sizeof(index));
                sprites[i]->transformations[t] = transformations[index];
            }
        }

        //Load ordered sprite name index
        spriteNames = new KeyValuePair<BaseSprite>[spriteCount];
        for(unsigned int i = 0; i < spriteCount; i++){
            unsigned short index = 0;

            file->read((char*) &index, sizeof(index));
            spriteNames[i].value = sprites[index];
            byte nameLen = 0;
            file->read((char*) &nameLen, sizeof(nameLen));
            spriteNames[i].key = new char[nameLen + 1];
            file->readString(spriteNames[i].key, nameLen);
            spriteNames[i].key[nameLen] = '\0';
            sprites[index]->name = spriteNames[i].key;
        }

        //Load sprite sets
        file->read((char*) &spriteSetCount, sizeof(spriteSetCount));

        spriteSets = new SpriteSet*[spriteSetCount];
        for(unsigned int i = 0; i < spriteSetCount; i++){
            byte spriteSetSize = 0;
            file->read((char*) &spriteSetSize, sizeof(spriteSetSize));
            spriteSets[i] = new SpriteSet(spriteSetSize);
            for(int j = 0; j < spriteSetSize; j++){
                unsigned short spriteIndex = 0;
                file->read((char*) &spriteIndex, sizeof(spriteIndex));
                spriteSets[i]->sprites[j] = getSprite(spriteIndex);
                spriteSets[i]->index = i;
            }
        }

        //Load ordered sprite set name index
        spriteSetNames = new KeyValuePair<SpriteSet>[spriteSetCount];
        for(unsigned int i = 0; i < spriteSetCount; i++){
            unsigned short index = 0;
            file->read((char*)&index, sizeof(index));
            spriteSetNames[i].value = spriteSets[index];
            byte nameLen = 0;
            file->read((char*)&nameLen, sizeof(nameLen));
            spriteSetNames[i].key = new char[nameLen + 1];
            file->readString(spriteSetNames[i].key, sizeof(char) * nameLen);
            spriteSetNames[i].key[nameLen] = '\0';
        }

        Log << "Sprites loaded";

        delete file;
    }
}
#ifdef _PC_
void SpriteManager::loadRaw(const char* file){
    //Open xml document.
    pugi::xml_document doc;
    pugi::xml_parse_result loadResult = doc.load_file(file);

    Log << "Load Result: " << loadResult.description();

    //Parse transformations
    std::vector<char*> transformNames;
    std::vector<BaseTransformation*> transforms;
    pugi::xml_node transformsNode = doc.first_child().child("transformations");

    Log << "Transformations: ";
    for(pugi::xml_node node = transformsNode.first_child(); node; node = node.next_sibling()){
        parseTransformation(node, transformNames, transforms);
    }

    //Parse spritesheets
    std::vector<char*> sheetNames;
    pugi::xml_node sheets = doc.first_child().child("spritesheets");

    Log << "Spritesheets: ";

    for(pugi::xml_node node = sheets.first_child(); node; node = node.next_sibling()){
        Log << "Spritesheet " << node.attribute("name").value();
        char* sheetName = new char[strlen(node.attribute("name").value()) + 1];
        strcpy(sheetName, node.attribute("name").value());
        sheetName[strlen(node.attribute("name").value())] = 0;
        
        sheetNames.push_back(sheetName);
    }

    //Allocate textures for sprite sheets.
    textures = new sf::Texture[sheetNames.size()];
    textureSprites = new sf::Sprite[sheetNames.size()];
    textureNames = new char*[sheetNames.size()];

    //Load sheet textures.
    for(unsigned int i = 0; i < sheetNames.size(); i++){
        char* textureName = new char[strlen(sheetNames.at(i)) + 5];
        strcpy(textureName, sheetNames.at(i));
        strcat(textureName, ".tga");
        if(!textures[i].loadFromFile(textureName)){
            Log << LL_C << "Failed to load texture.";
            continue;
        }
		textureSprites[i].setTexture(textures[i], true);
        textureNames[i] = sheetNames.at(i);
    }
    sheetCount = sheetNames.size();

    //Parse sprites
    pugi::xml_node spritesNodes = doc.first_child().child("sprites");
    std::vector<BaseSprite*> spritesList;
    std::vector<char*> namesList;
    std::vector<pugi::xml_node> nonstaticNodes;

    std::vector<SpriteSet*> setsList;
    std::vector<char*> setNamesList;

    //Parse static sprite definitions first.
    Log << "Sprites: ";
    for(pugi::xml_node node = spritesNodes.first_child(); node; node = node.next_sibling()){
        if(strcmp(node.name(), "sprite") == 0){

            for(pugi::xml_node tnode = node.first_child(); tnode; tnode = tnode.next_sibling()){
                parseTransformation(tnode, transformNames, transforms);
            }

            StaticSprite* sprite = new StaticSprite(getStringIndex(&sheetNames, node.attribute("sheet").value()), spritesList.size(),
                textures[getStringIndex(&sheetNames, node.attribute("sheet").value())],
                node.attribute("x").as_int(), node.attribute("y").as_int(),
                node.attribute("width").as_int(), node.attribute("height").as_int());
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            Log << "Name: " << name << ", Sheet: " << sprite->sheet
                << ", x: " << sprite->drawSprite.getTextureRect().left << ", y: " << sprite->drawSprite.getTextureRect().top
                << ", Width: " << sprite->drawSprite.getTextureRect().width << ", Height: " << sprite->drawSprite.getTextureRect().height;
            
            //Resolve transformations
            getSpriteTransformations(node, sprite, transformNames, transforms);
            
            spritesList.push_back(sprite);
            namesList.push_back(name);
        }else{
            //If not static sprite then push to list to deal with later.
            nonstaticNodes.push_back(node);
        }
    }

    //Process non static sprites
    for(unsigned int n = 0; n < nonstaticNodes.size(); n++){
        pugi::xml_node node = nonstaticNodes.at(n);
        if(strcmp(node.name(), "animatedsprite") == 0){//Animated sprite

            for(pugi::xml_node tnode = node.first_child(); tnode; tnode = tnode.next_sibling()){
                if(strcmp(tnode.name(), "frame") != 0)
                    parseTransformation(tnode, transformNames, transforms);
            }

            std::vector<SpriteFrame*> frames;
            for(pugi::xml_node frame = node.first_child(); frame; frame = frame.next_sibling()){
                if(strcmp(frame.name(), "frame") == 0){
                    SpriteFrame* spriteframe = new SpriteFrame();
                    spriteframe->duration = frame.attribute("duration").as_int();
                    spriteframe->index = getStringIndex(&namesList, frame.attribute("sprite").value());
                    frames.push_back(spriteframe);
                }
            }
            AnimatedSprite* sprite = new AnimatedSprite(frames.size(), spritesList.size());
            
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            //Load sprite frames.
            Log << "Name: " << name << " Frames: " << (int)frames.size();
            for(unsigned int i = 0; i < frames.size(); i++){
                sprite->frames[i].duration = frames.at(i)->duration;
                sprite->frames[i].index = frames.at(i)->index;
                sprite->frames[i].sprite = spritesList.at(sprite->frames[i].index);
                Log << "Frame: " << i << ", Sprite Index: " << sprite->frames[i].index
                        << ", Duration: " << sprite->frames[i].duration << "ms.";

				delete frames.at(i); //Delete temp frame
            }
			frames.clear();

            sprite->width = sprite->frames[0].sprite->width;
            sprite->height = sprite->frames[0].sprite->height;
            
            //Resolve transformations
            getSpriteTransformations(node, sprite, transformNames, transforms);

            addDynamicSprite(sprite);
            spritesList.push_back(sprite);
            namesList.push_back(name);
        }else if(strcmp(node.name(), "layeredsprite") == 0){//Layered sprite

            for(pugi::xml_node tnode = node.first_child(); tnode; tnode = tnode.next_sibling()){
                if(strcmp(tnode.name(), "layer") != 0)
                    parseTransformation(tnode, transformNames, transforms);
            }

            std::vector<BaseSprite*> layers;
            for(pugi::xml_node layer = node.first_child(); layer; layer = layer.next_sibling()){
                if(strcmp(layer.name(), "layer") == 0)
                    layers.push_back(spritesList.at(getStringIndex(&namesList, layer.attribute("sprite").value())));
            }
            LayeredSprite* sprite = new LayeredSprite(layers.size(), spritesList.size());
            
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            //Load sprite layers.
            Log << "Name: " << name;
            for(unsigned int i = 0; i < layers.size(); i++){
                sprite->layers[i] = layers.at(i);
                Log << "Layer: " << i << ", Sprite Index: " << sprite->layers[i]->index;
            }
			layers.clear();
            sprite->width = sprite->layers[0]->width;
            sprite->height = sprite->layers[0]->height;
            spritesList.push_back(sprite);
            namesList.push_back(name);
        }
        else if(strcmp(node.name(), "set") == 0){//Set
            std::vector<BaseSprite*> setSprites;
            for(pugi::xml_node sprite = node.first_child(); sprite; sprite = sprite.next_sibling()){
                setSprites.push_back(spritesList.at(getStringIndex(&namesList, sprite.attribute("name").value())));
            }
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            Log << "Name: " << name;

            //Load set sprites.
            SpriteSet* set = new SpriteSet(setSprites.size());
            for(unsigned int i = 0;i < setSprites.size(); i++){
                set->sprites[i] = setSprites.at(i);
                Log << "Set Sprite: " << i << ", Sprite Index: " << set->sprites[i]->index;
            }
            setsList.push_back(set);

            setNamesList.push_back(name);
        }
    }

    //Copy sprites into sprite array
    spriteCount = spritesList.size();
    sprites = new BaseSprite*[spriteCount];
    for(unsigned short i = 0; i < spriteCount; i++){
        sprites[i] = spritesList.at(i);
    }
	spritesList.clear();

    //Copy transformations to array.
    transformationCount = transforms.size();
    transformations = new BaseTransformation*[transformationCount];
    transformationNames = new char*[transformationCount];
    for(unsigned short i = 0; i < transformationCount; i++){
        transformationNames[i] = transformNames.at(i);
        transformations[i] = transforms.at(i);
        transformations[i]->index = i;
    }

    //Copy sprite names into sprite names array while sorting them by name
    //Simple insertion sort.
    spriteNames = new KeyValuePair<BaseSprite>[spriteCount];
    for(unsigned short i = 0; i < namesList.size(); i++){
        sprites[i]->name = namesList.at(i);
        KeyValuePair<BaseSprite>::insertSort(sprites[i], sprites[i]->name, spriteNames, namesList.size());
    }

    //Copy sprite sets into sprite set array
    spriteSetCount = setsList.size();
    spriteSets = new SpriteSet*[spriteSetCount];
    for(unsigned int i = 0; i < spriteSetCount; i++){
        spriteSets[i] = setsList.at(i);
        spriteSets[i]->index = i;
    }

    //Copy sprite set names into name array while sorting.
    spriteSetNames = new KeyValuePair<SpriteSet>[spriteSetCount];
    for(unsigned int i = 0; i < setNamesList.size(); i++){
        spriteSets[i]->index = i;
        KeyValuePair<SpriteSet>::insertSort(spriteSets[i], setNamesList.at(i), spriteSetNames, setNamesList.size());
    }
}
void SpriteManager::save(const char* file){
    
    //Open destination file.
    Log << LC_F << LL_D << "Saving sprites";
    std::ofstream fileWriter;
    fileWriter.open(file, std::ios::binary | std::ios::out);
    if(fileWriter.fail()){
        Log << LL_C << "Open file failed.";
        return;
    }

    //Write transformations
    fileWriter.write((char*) &transformationCount, sizeof(transformationCount));
    for(unsigned short i = 0; i < transformationCount; i++){
        byte nameLen = strlen(transformationNames[i]);
        fileWriter.write((char*) &nameLen, sizeof(nameLen));
        fileWriter.write(transformationNames[i], nameLen);
        
        //Write type code.
        byte type = (byte)transformations[i]->type;
        fileWriter.write((char*) &type, sizeof(type));

        //Write transformation type specific data.
        if(type == BaseTransformation::tt_Matrix){
            MatrixTransformation* transform = (MatrixTransformation*)transformations[i];
            fileWriter.write((char*) &transform->transformFlags, sizeof(transform->transformFlags));

            if(transform->transformFlags & MatrixTransformation::to_Rotate){
                fileWriter.write((char*) &transform->rAngle, sizeof(transform->rAngle));
                fileWriter.write((char*) &transform->rX, sizeof(transform->rX));
                fileWriter.write((char*) &transform->rY, sizeof(transform->rY));
            }

            if(transform->transformFlags & MatrixTransformation::to_Scale){
                fileWriter.write((char*) &transform->sX, sizeof(transform->sX));
                fileWriter.write((char*) &transform->sY, sizeof(transform->sY));
            }

            if(transform->transformFlags & MatrixTransformation::to_Translate){
                fileWriter.write((char*) &transform->tX, sizeof(transform->tX));
                fileWriter.write((char*) &transform->tY, sizeof(transform->tY));
            }
        }
    }
    
    //Write sheet definitions
    fileWriter.write((char*) &sheetCount, sizeof(sheetCount));
    for(unsigned short i = 0; i < sheetCount; i++){
        byte nameLen = strlen(textureNames[i]);
        fileWriter.write((char*) &nameLen, sizeof(nameLen));
        fileWriter.write(textureNames[i], nameLen);
    }

    //Write all sprites.
    fileWriter.write((char*) &spriteCount, sizeof(spriteCount));
    for(unsigned short i = 0; i < spriteCount; i++){
        sprites[i]->serialize(fileWriter);

        //Write sprite transformations
        byte transformationCount = sprites[i]->transformationCounter;
        fileWriter.write((char*) &transformationCount, sizeof(transformationCount));
        for(byte t = 0; t < transformationCount; t++){
            unsigned short index = sprites[i]->transformations[t]->index;
            fileWriter.write((char*) &index, sizeof(index));
        }
    }
    
    //Write sprite name index.
    for(int i = 0; i < spriteCount; i++){
        fileWriter.write((char*) &spriteNames[i].value->index, sizeof(spriteNames[i].value->index));
        unsigned char nameLen = strlen(spriteNames[i].key);
        fileWriter.write((char*) &nameLen, sizeof(nameLen));
        fileWriter.write(spriteNames[i].key, nameLen);
    }

    //Write sprite sets
    fileWriter.write((char*) &spriteSetCount, sizeof(spriteSetCount));
    for(int i = 0; i < spriteSetCount; i++){
        fileWriter.write((char*) &spriteSets[i]->numSprites, sizeof(spriteSets[i]->numSprites));
        for(int j = 0; j < spriteSets[i]->numSprites; j++){
            fileWriter.write((char*) &spriteSets[i]->sprites[j]->index, sizeof(spriteSets[i]->sprites[j]->index));
        }
    }
    
    //Write sprite set name index
    for(int i = 0; i < spriteSetCount; i++){
        fileWriter.write((char*) &spriteSetNames[i].value->index, sizeof(spriteSetNames[i].value->index));
        unsigned char nameLen = strlen(spriteSetNames[i].key);
        fileWriter.write((char*) &nameLen, sizeof(nameLen));
        fileWriter.write(spriteSetNames[i].key, nameLen);
    }

    fileWriter.close();
}

/** 
* Get index of string in vector.
*/
int SpriteManager::getStringIndex(std::vector<char*>* strings, const char* name){
    for(unsigned int i = 0; i < strings->size(); i++){
        if(strcmp(name, strings->at(i)) == 0){
            return i;
        }
    }
    return NO_SPRITE; //Should crash
}

void SpriteManager::parseTransformation(pugi::xml_node node, std::vector<char*>& transformNames, std::vector<BaseTransformation*>& transforms){
    if(strcmp(node.name(), "transformation") != 0){
        Log << "Transformation " << node.attribute("name").value() << " of type " << node.name();
        char* name = new char[strlen(node.attribute("name").value()) + 1];
        strcpy(name, node.attribute("name").value());
        name[strlen(node.attribute("name").value())] = 0;
        transformNames.push_back(name);

        if(strcmp(node.name(), "matrix") == 0){
            MatrixTransformation* transform = new MatrixTransformation();
            if(node.attribute("translateX").as_int() != 0)
                transform->translate(node.attribute("translateX").as_int(), 0);
            if(node.attribute("translateY").as_int() != 0)
                transform->translate(0, node.attribute("translateY").as_int());

            if(node.attribute("flipH").as_bool())
                transform->flipHorizontally();

            if(node.attribute("flipV").as_bool())
                transform->flipVertically();

            if(node.attribute("scaleX").as_float() != 0.0){
                transform->scale(node.attribute("scaleX").as_float(), 1.0);
            }

            if(node.attribute("scaleY").as_float() != 0.0){
                transform->scale(1.0, node.attribute("scaleY").as_float());
            }

            if(node.attribute("rotate").as_float() != 0.0){
                transform->rotate(node.attribute("rotate").as_float(), node.attribute("rotateX").as_float(), node.attribute("rotateY").as_float());
            }

            transforms.push_back(transform);
        }
    }
}

void SpriteManager::getSpriteTransformations(pugi::xml_node node, BaseSprite* sprite, std::vector<char*>& transformNames,
    std::vector<BaseTransformation*>& transforms){

    if(node.first_child()){
        Log << "Transformations: ";
    }
    int embeddedCounter = 0;
    for(pugi::xml_node tnode = node.first_child(); tnode; tnode = tnode.next_sibling()){
        if(strcmp(tnode.name(), "transformation") == 0){
            Log << "\t" << tnode.attribute("name").value();
            for(unsigned short i = 0; i < transformNames.size(); i++){
                if(strcmp(transformNames.at(i), tnode.attribute("name").value()) == 0){
                    sprite->apply(transforms.at(i));
                    break;
                }
            }
        }else if(strcmp(tnode.name(), "matrix") == 0){
            embeddedCounter+=1;
            sprite->apply(transforms.at(transforms.size() - embeddedCounter)); //Reverses order.
        }
    }
}
#endif

/** 
* Clear all sprites and textures from memory.
*/
SpriteManager::~SpriteManager(){

    dynamicList.clear();
    
    //Clear sprite definitions
    for(int i = 0; i < spriteCount; i++){
        delete sprites[i];
        delete spriteNames[i].key;
		spriteNames[i].key = 0;
        sprites[i] = 0;
    }
    delete sprites;
    sprites = 0;

    delete spriteNames;
    spriteNames = 0;

    //Clear sprite set definitions
    for(int i = 0; i < spriteSetCount; i++){
        delete spriteSets[i];
		delete spriteSetNames[i].key;
        spriteSets[i] = 0;
    }
    delete spriteSets;
    spriteSets = 0;

    delete spriteSetNames;
    spriteSetNames = 0;

    //Clear texture names
    for(int i = 0; i < sheetCount; i++){
        delete textureNames[i];
        textureNames[i] = 0;
    }

	delete textureNames;
	textureNames = 0;
    
}