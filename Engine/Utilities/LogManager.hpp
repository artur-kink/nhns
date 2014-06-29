#ifndef _LOGMANAGER_
#define _LOGMANAGER_

#include "Logger.hpp"

#define Log (LogManager::getInstance()->newCall()); (*LogManager::getInstance())

/**
 * Main logging class that handles logging in engine.
 */
class LogManager:public Logger{
private:
    /** Singleton instance. */
    static LogManager* instance;

#define COPY_SIZE 4
    
    /** Current number of copy loggers. */
    unsigned short copyLoggersCount;

    /** List of loggers to copy output to. */
    Logger* copyLoggers[COPY_SIZE];
protected:
    LogManager();
    virtual void write(const char* str);
public:
    static LogManager* getInstance();
    
    void addCopyLogger(Logger* logger);
    
    LogManager& operator>>(Logger* logger);

    virtual void setLevel(LogLevel l);
    virtual void setChannel(LogChannel c);
    virtual void setLevelFilter(LogLevel l);
    virtual void setChannelFilter(unsigned short c);
    
    virtual void newCall();

    virtual void close();
    ~LogManager();
};

#endif