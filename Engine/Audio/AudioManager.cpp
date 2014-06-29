#include "AudioManager.hpp"

/**
 * Initialize empty AudioManager.
 */
AudioManager::AudioManager(){
    audioObjects = 0;
    objectCount = 0;
}

/**
 * Find and play audio object with given name.
 * @param name Name of AudioObject to play.
 */
void AudioManager::play(const char* name){
    play(getAudioObject(name));
}

/**
 * Play given audio object.
 * @param object AudioObject to play.
 */
void AudioManager::play(AudioObject* object){
#ifdef _PC_
    if(object->type == AudioObject::at_LoadOnUse){
        music.openFromFile(object->fileName);
        music.setLoop(true);
        music.play();
    }else{
        //Find available sound and play object on it.
        for(int i = 0; i < maxSounds; i++){
            if(sounds[i].getStatus() == sf::Sound::Stopped){
                sounds[i].setBuffer(object->soundBuffer);
                sounds[i].play();
                break;
            }
        }
    }
#endif
}

void AudioManager::stopAll(){
#ifdef _PC_
    for(int i = 0; i < maxSounds; i++){
        if(sounds[i].getStatus() != sf::Sound::Stopped){
            sounds[i].stop();
        }
    }
    music.stop();
#endif
}

/**
 * Get AudioObject with given name.
 * @param name Name of AudioObject to find.
 */
AudioObject* AudioManager::getAudioObject(const char* name){
    return KeyValuePair<AudioObject>::findValue(audioNames, objectCount, name);
}

void AudioManager::load(const char* path){
    Log << LC_A << LL_D <<"Loading audio definition file: " << path;
    //Open file
    FileHandler fileHandler;
    MemoryPool* file = fileHandler.readFile(path);
    
    //If file reading succeeded.
    if(file->getBuffer()){

        //Load audio definitions
        file->read((char*) &objectCount, sizeof(objectCount));
        audioObjects = new AudioObject*[objectCount];
   
        Log << "Audio Objects Found: " << objectCount;
        for(unsigned short i = 0; i < objectCount; i++){
            audioObjects[i] = new AudioObject();
            audioObjects[i]->index = i;
            audioObjects[i]->deserialize(file);

            Log << "File: " << audioObjects[i]->fileName;
#ifdef _PC_
            if(audioObjects[i]->type == AudioObject::at_Preloaded &&
                !audioObjects[i]->soundBuffer.loadFromFile(audioObjects[i]->fileName)){
                Log << "Failed to load audio file.";
            }
#endif
        }

        //Load ordered sprite name index
        audioNames = new KeyValuePair<AudioObject>[objectCount];
        for(unsigned int i = 0; i < objectCount; i++){
            unsigned short index = 0;

            file->read((char*) &index, sizeof(index));
            audioNames[i].value = audioObjects[index];
            byte nameLen = 0;
            file->read((char*) &nameLen, sizeof(nameLen));
            audioNames[i].key = new char[nameLen + 1];
            file->readString(audioNames[i].key, nameLen);
            audioNames[i].key[nameLen] = '\0';
            audioObjects[index]->name = audioNames[i].key;
        }

        Log << "Audio Objects loaded.";

        delete file;
    }
}

#ifdef _PC_
void AudioManager::loadRaw(const char* file){
//Open xml document.
    pugi::xml_document doc;
    pugi::xml_parse_result loadResult = doc.load_file(file);

    Log << "Load Result: " << loadResult.description();
    
    //Parse audio objects
    std::vector<AudioObject*> audioList;
    std::vector<char*> namesList;

    Log << "Audio Objects: ";
    for(pugi::xml_node node = doc.first_child().first_child(); node; node = node.next_sibling()){
        if(strcmp(node.name(), "audio") == 0){

            AudioObject* audioObject = new AudioObject();
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            audioObject->fileName = new char[strlen(node.attribute("file").value()) + 1];
            strcpy(audioObject->fileName, node.attribute("file").value());
            audioObject->fileName[strlen(node.attribute("file").value())] = '\0';

            audioObject->name = name;
            
            if(node.attribute("preload").as_bool())
                audioObject->type = AudioObject::at_Preloaded;
            else
                audioObject->type = AudioObject::at_LoadOnUse;
            
            Log << "Name: " << name << ", File: " << audioObject->fileName;
            
            audioList.push_back(audioObject);
            namesList.push_back(name);
        }
    }

    //Copy sprites into sprite array
    objectCount = audioList.size();
    audioObjects = new AudioObject*[objectCount];
    for(unsigned short i = 0; i < objectCount; i++){
        audioObjects[i] = audioList.at(i);
        audioObjects[i]->index = i;
    }

    //Copy sprite names into sprite names array while sorting them by name
    audioNames = new KeyValuePair<AudioObject>[objectCount];
    for(unsigned short i = 0; i < namesList.size(); i++){
        audioObjects[i]->name = namesList.at(i);
        KeyValuePair<AudioObject>::insertSort(audioObjects[i], audioObjects[i]->name, audioNames, objectCount);
    }

	audioList.clear();
    
    Log << "Loaded raw audio file.";
}

void AudioManager::save(const char* file){
    //Open destination file.
    Log << LC_F << LL_D << "Saving audio objects.";
    std::ofstream fileWriter;
    fileWriter.open(file, std::ios::binary | std::ios::out);
    if(fileWriter.fail()){
        Log << LC_F << LL_C << "Open file failed.";
        return;
    }

    //Write audio objects.
    fileWriter.write((char*) &objectCount, sizeof(objectCount));
    for(unsigned short i = 0; i < objectCount; i++){
        audioObjects[i]->serialize(fileWriter);
    }
    
    Log << LC_F << LL_D << "Saving name index.";
    //Write audio object name index.
    for(int i = 0; i < objectCount; i++){
        fileWriter.write((char*)&audioNames[i].value->index, sizeof(audioNames[i].value->index));
        byte nameLen = strlen(audioNames[i].key);
        fileWriter.write((char*)&nameLen, sizeof(nameLen));
        fileWriter.write(audioNames[i].key, nameLen);
    }

    fileWriter.close();
    Log << LC_F << LL_D << "Saved audio objects.";
}
#endif

/**
 * Destructor, stop and clear all audio objects.
 */
AudioManager::~AudioManager(){
    //Stop any playing audio.
    stopAll();
    delete audioNames;
    audioNames = 0;
    delete audioObjects;
    audioObjects = 0;
}