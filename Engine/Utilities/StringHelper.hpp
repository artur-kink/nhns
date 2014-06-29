#ifndef _STRINGHELPER_
#define _STRINGHELPER_

#include <stdarg.h>
#include <cstring>
#include <sstream>

#include "MemoryPool.hpp"

#define String StringHelper

/** 
 * Helper class for strings.
 * Uses the c string library naming conventions.
 * This class handles string memory cleanup itself,
 * for this reason the returned strings may not be deleted.
 * Any pointer to a string returned by this class may
 * become invalid if a new string has since been returned
 * by this class. For this reason it is suggested that
 * any string returned by this class be used immediately
 * to avoid corruption.
 */
class StringHelper{
private:
    /** Internal memory pool that contains returned strings. */
    static MemoryPool stringPool;
    /** Internal memory pool for concatenated strings. */
    static MemoryPool concatPool;
    static const char* write(const char* str);
#define STRING_LEN 511
public:
    
    static void init();
    
    static const char* itos(int value);
    static const char* uitos(unsigned int value);
    static const char* stos(short value);
    static const char* ustos(unsigned short value);
    static const char* ftos(float value);
    static const char* dtos(double value);
    static int stoi(const char* value);

    static const char* concat(int count, ...);
};

#endif