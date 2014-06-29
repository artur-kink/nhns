#ifndef _CONSOLELOGGER_
#define _CONSOLELOGGER_

#ifdef _PC_
#include <iostream>
#endif

#include "Logger.hpp"

/**
 * Logger that outputs entries to a system console.
 */
class ConsoleLogger: public Logger{
protected:
    virtual void write(const char* str);

    /** Has a newCall been made since the last write. */
    bool isNewCall;
public:
    ConsoleLogger();

    virtual void newCall();
};

#endif