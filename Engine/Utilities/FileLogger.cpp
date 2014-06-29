#include "FileLogger.hpp"

FileLogger::FileLogger(const char* name, char delim){
    isNewCall = true;
    delimiter = delim;

    pool.createPool(4096);

    //Open output file.
    FileHandler fileHandler;
    
    char *filename = new char[64];
    filename[0] = 0;
    DateTime dt = CalendarTime::getDateTime();
#ifdef _PC_
    strcpy(filename, "Log/");
#endif
    strcat(filename, name);
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.month));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.day));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.hour));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.minute));
    strcat(filename, "_");
    strcat(filename, StringHelper::ustos(dt.second));
    strcat(filename, ".txt");
    
    logFile = fileHandler.openFile(filename, FileHandler::fam_New);
    delete filename;
}

void FileLogger::write(const char* str){
    
    //Print entry info if new entry.
    if(isNewCall){
        isNewCall = false;//Infinite recursion if this is not set.
        write("\n");
        write(StringHelper::itos(Time::getInstance()->getTimeMilliseconds()));
        char delim[2];
        delim[0] = delimiter;
        delim[1] = 0;

        write(delim);
        write(Logger::LevelNames[level]);
        write(delim);
        write(Logger::ChannelNames[channels]);
        write(delim);
    }

    //For debug purposes do not cache output.
    //if(!pool.copyToPool(strlen(str), (void*)str)){
        pool.copyToPool(strlen(str), (void*)str);

        FileHandler writeHandler;
        writeHandler.write(logFile, pool.getLength(), (char*)pool.getBuffer());
        pool.clear();
        //pool.copyToPool(strlen(str), (void*)str);
    //}
}

void FileLogger::newCall(){
    isNewCall = true;
}

void FileLogger::close(){
    Logger::close();
    FileHandler closeFile;
    closeFile.closeFile(logFile);
}

FileLogger::~FileLogger(){
    close();
}
