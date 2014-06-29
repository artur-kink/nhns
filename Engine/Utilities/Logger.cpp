#include "Logger.hpp"

const char* Logger::endl = "\n";
const char* Logger::LevelNames[] = {
    "Critical",
    "Warning",
    "Info",
    "Debug",
    "Verbose"
};

const char* Logger::ChannelNames[] = {
    "",
    "Engine",
    "Graphics",
    "Filesystem",
    "Audio",
    "Other",
    ""
};

Logger::Logger(){
    level = 0;
    channels = 1;
    levelFilter = ll_Critical;
    channelFilter = 0xFF;
    filterLocked = false;
}

/**
 * Write string to output.
 * @param str String to write.
 */
Logger& Logger::operator<<(const char* str){
    //Check for special character codes.
    if(str[0] == 0){
        setLevel((LogLevel)str[1]);
        return *this;
    }else if(str[0] == 1){
        setChannel((LogChannel)str[1]);
        return *this;
    }
    
    if(!isFiltered()){
        write(str);
    }

    return *this;
}

/**
 * Write integer to output.
 * @param integer Integer to write.
 */
Logger& Logger::operator<<(int integer){
    return operator<<(StringHelper::itos(integer));
}

Logger& Logger::operator<<(byte b){
    return operator<<(StringHelper::ustos((unsigned short)b));
}

Logger& Logger::operator<<(unsigned int integer){
    return operator<<(StringHelper::uitos(integer));
}

Logger& Logger::operator<<(short s){
    return operator<<(StringHelper::stos(s));
}

Logger& Logger::operator<<(unsigned short s){
    return operator<<(StringHelper::ustos(s));
}

Logger& Logger::operator<<(float f){
    return operator<<(StringHelper::ftos(f));
}

Logger& Logger::operator<<(double d){
    return operator<<(StringHelper::dtos(d));
}

/**
 * Write a std string to output.
 * @param str String to write.
 */
Logger& Logger::operator<<(std::string str){
    return operator<<(str.c_str());
}

/**
 * Set the current LogLevel for logger.
 */
void Logger::setLevel(LogLevel l){
    level = l;
}

/**
 * Set the current LogChannel for logger.
 */
void Logger::setChannel(LogChannel c){
    channels = c;
}

/**
 * A method called whenever a new Log message starts.
 */
void Logger::newCall(){
    
}

/**
 * Locks the logger so its filters cannot be changed.
 */
void Logger::lockFilter(){
    filterLocked = true;
}

/**
 * Enables logger to have its filters changed.
 */
void Logger::unlockFilter(){
    filterLocked = false;
}

/**
 * Sets the logger to filter any entires
 * with lower importance than given level.
 */
void Logger::setLevelFilter(LogLevel l){
    if(!filterLocked)
        levelFilter  = l;
}

/**
 * Sets the logger to filter any entries
 * not in given channels.
 * @param c Bitmap of LogChannel values.
 */
void Logger::setChannelFilter(unsigned short c){
    if(!filterLocked)
        channelFilter = c;
}

/**
 * Checks if a log entry would be ignored
 * based on current level and channel and filter settings.
 * @return true if entry would be ignored, false otherwise.
 */
bool Logger::isFiltered(){
    return (level > levelFilter || channelFilter & channels == 0);
}

/**
 * Pre destructor logger cleanup.
 */
void Logger::close(){
}
