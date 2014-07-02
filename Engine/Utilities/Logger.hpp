#ifndef _LOGGER_
#define _LOGGER_

#include <stdio.h>
#include <cstring>
#include <string>
#include "StringHelper.hpp"

/**
 * Abstract base class for a logger.
 */
class Logger{
    friend class LogManager;
private:

protected:
    Logger();

    /** Current log level. */
    unsigned short level;
    /** Current log channel. */
    unsigned short channels;

    /** Current log level filter. */
    unsigned short levelFilter;
    /** Current log channel filter. */
    unsigned short channelFilter;

    /** Are the filter settings locked from changing. */
    bool filterLocked;

    /**
     * Pure virtual function that writes log strings to the log's output.
     * @param str String to write.
     */
    virtual void write(const char* str) = 0;
public:

    /** 
     * Log verbosity levels. 
     * Filtering levels work by checking if an entry level
     * is at or below filter level, thus the levels are in
     * order of importance.
     */
    enum LogLevel{
        /** Errors. Fatal events. */
        ll_Critical = 0,
        /** Unusual or unexpected results, possibly errors. */
        ll_Warning = 1,
        /** General info. */
        ll_Info = 2,
        /** Debug prints. */
        ll_Debug = 3,
        /** Extremely dense debug prints. */
        ll_Verbose = 4
    };

#define LOG_CRITICAL "\0\0"
#define LL_C LOG_CRITICAL
#define LOG_WARNING "\0\1"
#define LL_W LOG_WARNING
#define LOG_INFO "\0\2"
#define LL_I LOG_INFO
#define LOG_DEBUG "\0\3"
#define LL_D LOG_DEBUG
#define LOG_VERBOSE "\0\4"
#define LL_V LOG_VERBOSE

    /** LogLevel String names. */
    static const char* LevelNames[];

    /** 
     * Log entry source channel. Where the input originated.
     * Filtering channels works on a per channel basis which
     * is implemented as a bit flag.
     */
    enum LogChannel{
        /** General emgine code. */
        lc_Engine = 1,
        /** Graphics engine. */
        lc_Graphics = 2,
        /** Filesystem. */
        lc_Filesystem = 3,
        /** Audio. */
        lc_Audio = 4,
        /** Network. */
        lc_Network = 5,
        /** Any other not included sources. */
        lc_Other = 6
    };

#define LOG_ENGINE "\1\1"
#define LC_E LOG_ENGINE
#define LOG_GRAPHICS "\1\2"
#define LC_G LOG_GRAPHICS
#define LOG_FILESYSTEM "\1\3"
#define LC_F LOG_FILESYSTEM
#define LOG_AUDIO "\1\4"
#define LC_A LOG_AUDIO
#define LOG_NETWORK "\1\5"
#define LC_N LOG_NETWORK
#define LOG_OTHER "\1\6"
#define LC_O LOG_OTHER

    /** LogChannel string names. */
    static const char* ChannelNames[];
    /** A newline. */
    static const char* endl;

    virtual Logger& operator<<(const char* str);
    virtual Logger& operator<<(std::string str);
    virtual Logger& operator<<(byte b);
    virtual Logger& operator<<(int integer);
    virtual Logger& operator<<(unsigned int integer);
    virtual Logger& operator<<(short s);
    virtual Logger& operator<<(unsigned short s);
    virtual Logger& operator<<(double d);
    virtual Logger& operator<<(float f);

    virtual void close();

    virtual void setLevel(LogLevel l);
    virtual void setChannel(LogChannel c);
    virtual void newCall();

    virtual void lockFilter();
    virtual void unlockFilter();
    virtual void setLevelFilter(LogLevel l);
    virtual void setChannelFilter(unsigned short c);
    bool isFiltered();
};

#include "LogManager.hpp"

#endif