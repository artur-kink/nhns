#include "LogManager.hpp"

LogManager* LogManager::instance = new LogManager();

LogManager::LogManager(){
    
    //Clear garbage data.
    for(int i = 0; i < COPY_SIZE; i++){
        copyLoggers[i] = 0;
    }
    copyLoggersCount = 0;

    //Set core logger to accept all channels and levels.
    Logger::setChannelFilter(255);
    Logger::setLevelFilter(Logger::ll_Verbose);
    lockFilter();
}

/**
 * Get singleton instance.
 */
LogManager* LogManager::getInstance(){
    return LogManager::instance;
};

/**
 * Add a logger to copy output to.
 * @param logger Address to a logger to copy output to.
 */
void LogManager::addCopyLogger(Logger* logger){
    for(int i = 0; i < COPY_SIZE; i++){
        if(copyLoggers[i] == 0){
            copyLoggers[i] = logger;
            copyLoggersCount++;
            break;
        }
    }
}

/**
 * Add a logger to copy output to using >> convention.
 * @see LogManager::addCopyLogger
 */
LogManager& LogManager::operator>>(Logger* logger){
    addCopyLogger(logger);
    return *this;
}

void LogManager::write(const char* str){
    for(int i = 0; i < copyLoggersCount; i++){
        if(!copyLoggers[i]->isFiltered()){
            copyLoggers[i]->write(str);
        }
    }
}

void LogManager::setLevel(LogLevel l){
    for(int i = 0; i < copyLoggersCount; i++){
        copyLoggers[i]->setLevel(l);
    }
    Logger::setLevel(l);
}

void LogManager::setChannel(LogChannel c){
    for(int i = 0; i < copyLoggersCount; i++){
        copyLoggers[i]->setChannel(c);
    }
    Logger::setChannel(c);
}

void LogManager::newCall(){
    for(int i = 0; i < copyLoggersCount; i++){
        copyLoggers[i]->newCall();
    }
    Logger::newCall();
}

void LogManager::close(){
    for(int i = 0; i < copyLoggersCount; i++){
        copyLoggers[i]->close();
        copyLoggers[i] = 0;
    }
    copyLoggersCount = 0;
    Logger::close();
}

void LogManager::setLevelFilter(LogLevel l){
    for(int i = 0; i < copyLoggersCount; i++){
        copyLoggers[i]->setLevelFilter(l);
    }
    //Do not set filter for self, let copy filters do the filtering.
}

void LogManager::setChannelFilter(unsigned short c){
    for(int i = 0; i < copyLoggersCount; i++){
        copyLoggers[i]->setChannelFilter(c);
    }
}

LogManager::~LogManager(){
    close();
}