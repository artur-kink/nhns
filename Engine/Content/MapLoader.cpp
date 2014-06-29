#include "MapLoader.hpp"

/** 
* Loads binary map file.
*/
bool MapLoader::loadMap(const char* fileName, Map** map, RegionManager* regions){
    Log << LL_D << LC_F << "Loading map: " << fileName;
    //Open file stream.
    FileHandler mapFile;

	MemoryPool* file = mapFile.readFile(fileName);
    if(file && file->getBuffer()){
        //Get map name
		unsigned char mapNameLength = 0;
		file->read((char*)&mapNameLength, sizeof mapNameLength);
		char* mapNameChr = new char[mapNameLength+1];
		file->readString(mapNameChr, mapNameLength);
		mapNameChr[mapNameLength] = '\0';
		string mapName = mapNameChr;
		delete mapNameChr;

        //Get map parameters.
		unsigned short width = 0;
		file->read((char*)&width, sizeof width);
		unsigned short height = 0;
		file->read((char*)&height, sizeof height);

		Log << "Map Name: '" << mapName << "', Size: " << width << "x" << height;
		Map* loadMap = new Map(mapName, width, height);
		
        bool loadingRegions = false;
		unsigned short tile = 0;
		while(true){
            if(!loadingRegions){
                //Read tile number
                file->read((char*) &tile, sizeof tile);

                //End of tiles delimiter
                if (tile == 0xFFFF) {
                    loadingRegions = true;
                    continue;
                }
                unsigned char tileInfo = 0;
                file->read((char*) &tileInfo, sizeof tileInfo);
                //Check which tile info needs reading.
                if ((tileInfo & 2) != 0) {
                    unsigned short layer = 0;
                    file->read((char*) &layer, sizeof layer);
                    loadMap->tiles[tile][0] = layer;
                } else {
                    loadMap->tiles[tile][0] = NO_SPRITE;
                }
                if ((tileInfo & 4) != 0) {
                    unsigned short layer = 0;
                    file->read((char*) &layer, sizeof layer);
                    loadMap->tiles[tile][1] = layer;
                } else {
                    loadMap->tiles[tile][1] = NO_SPRITE;
                }
                if ((tileInfo & 8) != 0) {
                    unsigned short layer = 0;
                    file->read((char*) &layer, sizeof layer);
                    loadMap->tiles[tile][2] = layer;
                } else {
                    loadMap->tiles[tile][2] = NO_SPRITE;
                }
                if ((tileInfo & 16) != 0) {
                    unsigned short layer = 0;
                    file->read((char*) &layer, sizeof layer);
                    loadMap->tiles[tile][3] = layer;
                } else {
                    loadMap->tiles[tile][3] = NO_SPRITE;
                }
                if ((tileInfo & 32) != 0) {
                    unsigned short layer = 0;
                    file->read((char*) &layer, sizeof layer);
                    loadMap->tiles[tile][4] = layer;
                } else {
                    loadMap->tiles[tile][4] = NO_SPRITE;
                }
                if ((tileInfo & 64) != 0) {
                    unsigned char properties = 0;
                    file->read((char*) &properties, sizeof properties);
                    loadMap->tiles[tile].properties = properties;
                } else {
                    loadMap->tiles[tile].properties = 0;
                }
            }else{
                if(file->eor())
                    break;

				Region* region = new Region();
				//Load region name.
                byte namelen = 0;
                file->read((char*)&namelen, sizeof(namelen));
                file->readString((char*)&region->name, namelen);
                region->name[namelen] = 0;
				
				//Load region size and position
                file->read((char*)&region->x, sizeof(region->x));
                file->read((char*)&region->y, sizeof(region->y));
                file->read((char*)&region->width, sizeof(region->width));
                file->read((char*)&region->height, sizeof(region->height));
                regions->add(region);
            }
            //fileStream.peek();
		}
		delete file;
        *map = loadMap;
        Log << LL_D << "Map loaded.";
		return true;
	}
	Log << LL_C << "Failed to load map file.";
	
	return false;
}

#ifdef _PC_
/** 
* Save passed map to a binary file.
*/
void MapLoader::saveMap(Map* map, RegionManager* regionManager){
    Log << LC_F << LL_D << "Saving map";
    //Open file
    ofstream fileStream;
    fileStream.open(std::string(map->name + ".dat").c_str(), ios::out | ios::binary);
    
    //Write metadata.
    unsigned char nameLength = map->name.length();
    fileStream.write((char*)&nameLength, sizeof(nameLength));
    fileStream.write(map->name.c_str(), strlen(map->name.c_str()));
    fileStream.write((char*)&map->width, sizeof(map->width));
    fileStream.write((char*)&map->height, sizeof(map->height));
    
    //Write all tiles that need writing
    for(unsigned short i = 0; i < map->width*map->height; i++){
        //Find out if this tile has information.
        unsigned char tileInfo = 0;
        if(map->tiles[i][0] != NO_SPRITE) tileInfo = tileInfo|2;
        if(map->tiles[i][1] != NO_SPRITE) tileInfo = tileInfo|4;
        if(map->tiles[i][2] != NO_SPRITE) tileInfo = tileInfo|8;
        if(map->tiles[i][3] != NO_SPRITE) tileInfo = tileInfo|16;
        if(map->tiles[i][4] != NO_SPRITE) tileInfo = tileInfo|32;
        if(map->tiles[i].properties) tileInfo = tileInfo|64;
        
        //If tile has info then write it to file.
        if(tileInfo != 0){
            //Write tile number and what tile info is given.
            fileStream.write((char*)&i, sizeof(i));
            fileStream.write((char*)&tileInfo, sizeof(tileInfo));
            if(map->tiles[i][0] != NO_SPRITE) fileStream.write((char*)&map->tiles[i][0], sizeof(map->tiles[i][0]));
            if(map->tiles[i][1] != NO_SPRITE) fileStream.write((char*)&map->tiles[i][1], sizeof(map->tiles[i][1]));
            if(map->tiles[i][2] != NO_SPRITE) fileStream.write((char*)&map->tiles[i][2], sizeof(map->tiles[i][2]));
            if(map->tiles[i][3] != NO_SPRITE) fileStream.write((char*)&map->tiles[i][3], sizeof(map->tiles[i][3]));
            if(map->tiles[i][4] != NO_SPRITE) fileStream.write((char*)&map->tiles[i][4], sizeof(map->tiles[i][4]));
            if(map->tiles[i].properties) fileStream.write((char*)&map->tiles[i].properties, sizeof(map->tiles[i].properties));
        }
    }
    
    //Write end of tiles delimiter
    unsigned short del = 0xFFFF;
    fileStream.write((char*)&del, sizeof(del));
    //Write regions to map file.
    for(unsigned short i = 0; i < regionManager->getSize(); i++){
        if(regionManager->regions[i]){
            Region* region = regionManager->regions[i];
            byte namelen = strlen((char*)&region->name[0]);
            fileStream.write((char*)&namelen, sizeof(namelen));
            fileStream.write((char*)&region->name, namelen);
            
			fileStream.write((char*)&region->x, sizeof(region->x));
            fileStream.write((char*)&region->y, sizeof(region->y));
            fileStream.write((char*)&region->width, sizeof(region->width));
            fileStream.write((char*)&region->height, sizeof(region->height));
        }
    }
    
    //Done map save, close stream.
    fileStream.close();
    Log << LC_F << LL_D << "Map saved.";
}

/** Load an xml map file.
 * @param fileName File to load
 * @param map Pointer to unallocated map pointer. Must make new map.
 * @param regionManager RegionManager to load map regions into.
 * @param sprites SpriteManager to retrieve tile sprites from.
 */
bool MapLoader::loadRawMap(const char* fileName, Map** map, SpriteManager* sprites, RegionManager* regionManager){
    Log << LC_F << LL_D << "Loading Raw Map: " << fileName;
	pugi::xml_document doc;
    pugi::xml_parse_result loadResult = doc.load_file(fileName);
    if(loadResult.status != pugi::status_ok)
        return 0;

    //Get root node
	pugi::xml_node mapNode = doc.first_child();
    if(mapNode == 0 || strcmp(mapNode.name(),"map") != 0)
        return 0;

    *map = new Map(mapNode.attribute("name").value(), mapNode.attribute("width").as_int(), mapNode.attribute("height").as_int());
    Log << LC_F << LL_D << "Map: " << (*map)->name << "(" << (*map)->width << "x" << (*map)->height << ")";

    pugi::xml_node tiles = mapNode.first_child();

    //Loop all tiles and retrieve their values into map.
    int i = 0;
	for(pugi::xml_node node = tiles.first_child(); node; node = node.next_sibling()){
        (*map)->tiles[i][0] = sprites->getSpriteIndex(node.attribute("layer0").value());
        (*map)->tiles[i][1] = sprites->getSpriteIndex(node.attribute("layer1").value());
        (*map)->tiles[i][2] = sprites->getSpriteIndex(node.attribute("layer2").value());
        (*map)->tiles[i][3] = sprites->getSpriteIndex(node.attribute("layer3").value());
        (*map)->tiles[i][4] = sprites->getSpriteIndex(node.attribute("layer4").value());
        (*map)->tiles[i].properties = node.attribute("properties").as_int();
        i++;
    }

    //Retrieve all regions in map
	pugi::xml_node regions = tiles.next_sibling();
	for(pugi::xml_node node = regions.first_child(); node; node = node.next_sibling()){
		Region* region = new Region();
        regionManager->add(region);
        region->setName(node.attribute("name").value());
		region->setArea(node.attribute("x").as_int(), node.attribute("y").as_int(),
                node.attribute("width").as_int(), node.attribute("height").as_int());
    }

    Log << LC_F << LL_D << "Raw map loaded.";
    return 1;
}

void MapLoader::saveRawMap(Map* map, SpriteManager* sprites, RegionManager* regionManager){
	pugi::xml_document doc;
    pugi::xml_node mapNode = doc.append_child("map");
    mapNode.append_attribute("name") = map->name.c_str();
    mapNode.append_attribute("width") = StringHelper::itos(map->width);
    mapNode.append_attribute("height") = StringHelper::itos(map->height);

    //Save all tiles
    pugi::xml_node tilesNode = mapNode.append_child("tiles");
    for(int tile = 0; tile < map->width*map->height; tile++){
        pugi::xml_node tileNode = tilesNode.append_child("tile");
        for(int layer = 0; layer < LAYERS; layer++){
            if(map->tiles[tile][layer] != NO_SPRITE){
                tileNode.append_attribute(StringHelper::concat(2, "layer", StringHelper::itos(layer))) = sprites->getSprite(map->tiles[tile][layer])->name;
            }else{
                tileNode.append_attribute(StringHelper::concat(2, "layer", StringHelper::itos(layer))) = "";
            }
        }
        tileNode.append_attribute("properties") = StringHelper::itos(map->tiles[tile].properties);
    }

    //Save all regions
    pugi::xml_node regionsNode = mapNode.append_child("regions");
    for(int region = 0; region < regionManager->getSize(); region++){
        if(regionManager->regions[region] != 0){
            Region* r = regionManager->regions[region];
            pugi::xml_node regionNode = regionsNode.append_child("region");
            regionNode.append_attribute("name") = r->name;
            regionNode.append_attribute("x") = StringHelper::itos(r->x);
            regionNode.append_attribute("y") = StringHelper::itos(r->y);
            regionNode.append_attribute("width") = StringHelper::itos(r->width);
            regionNode.append_attribute("height") = StringHelper::itos(r->height);
        }
    }
    doc.save_file((map->name + ".xml").c_str());
}
#endif