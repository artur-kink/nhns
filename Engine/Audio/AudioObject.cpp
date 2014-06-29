#include "AudioObject.hpp"

AudioObject::AudioObject(){
    name = 0;
    fileName = 0;
}

#ifdef _PC_
void AudioObject::serialize(std::ofstream& destination){
    //Write filename.
    byte fileLen = strlen(fileName);
    destination.write((char*)&fileLen, sizeof(fileLen));
    destination.write(fileName, fileLen);
    
    //Write audio object type.
    destination.write((char*)&type, sizeof(type));
}
#endif

void AudioObject::deserialize(MemoryPool* source){
    //Load file name
    byte fileNameLen = 0;
    source->read((char*) &fileNameLen, sizeof(fileNameLen));
    fileName = new char[fileNameLen + 1];
    source->readString(fileName, fileNameLen);
    fileName[fileNameLen] = '\0';

    //Load audio object type.
    source->read((char*) &type, sizeof(type));
}

AudioObject::~AudioObject(){
    //Do not delete name as that is stored in the AudioManager
    name = 0;
    if(fileName)
        delete fileName;
    fileName = 0;
}