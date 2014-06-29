#ifndef _FILELOGGER_
#define _FILELOGGER_

#include "FileHandler.hpp"

#include "Logger.hpp"
#include "Time.hpp"
#include "CalendarTime.hpp"
#include "StringHelper.hpp"
#include "MemoryPool.hpp"

/**
 * Logger that writes entries to a file.
 * Uses csv formatting.
 */
class FileLogger : public Logger{
private:
    /** File where output is written. */
    File logFile;

    /** A pool for write buffering. */
    MemoryPool pool;

    /** Has newCall been called since last write. */
    bool isNewCall;
    
protected:
    virtual void write(const char* str);

public:
	FileLogger(const char* name, char delim);
	char delimiter;

    virtual void close();
    virtual void newCall();

    ~FileLogger();

};

#endif