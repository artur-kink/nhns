#include "StringHelper.hpp"

MemoryPool StringHelper::stringPool;
MemoryPool StringHelper::concatPool;

/**
 * Initializes the StringHelper, without this call the helper cannot be used.
 */
void StringHelper::init(){
    stringPool.createPool(STRING_LEN + 1);
    concatPool.createPool(STRING_LEN + 1);
}

/** 
 * Internal method used to write a string to the string pool.
 * @param str String to write.
 */
const char* StringHelper::write(const char* str){
    int len = strlen(str) + 1;
    char* returnStr = (char*)StringHelper::stringPool.allocate(len);
    if(!returnStr){
        stringPool.clear();
        returnStr = (char*)stringPool.allocate(len);
    }
    strcpy(returnStr, str);
    return (const char*)returnStr;
}

/**
 * Converts int to string.
 * @param value The int to convert.
 * @return String representation of value.
 */
const char* StringHelper::itos(int value){
    std::ostringstream sstream;
    sstream << value;
    const char* returnStr = write(sstream.str().c_str());
    return returnStr;
}

/**
 * Converts an unsigned int to string.
 * @param value The unsigned int to convert.
 * @return String representation of value.
 */
const char* StringHelper::uitos(unsigned int value){
    std::ostringstream sstream;
    sstream << value;
    const char* returnStr = write(sstream.str().c_str());
    return returnStr;
}

/**
 * Converts a short to string.
 * @param value The short to convert.
 * @return String representation of value.
 */
const char* StringHelper::stos(short value){
    std::ostringstream sstream;
    sstream << value;
    const char* returnStr = write(sstream.str().c_str());
    return returnStr;
}

/**
 * Converts an unsigned short to string.
 * @param value The unsigned short to convert.
 * @return String representation of value.
 */
const char* StringHelper::ustos(unsigned short value){
    std::ostringstream sstream;
    sstream << value;
    const char* returnStr = write(sstream.str().c_str());
    return returnStr;
}

/**
 * Converts a float to string.
 * @param value The float to convert.
 * @return String representation of value.
 */
const char* StringHelper::ftos(float value){
    std::ostringstream sstream;
    sstream << value;
    const char* returnStr = write(sstream.str().c_str());
    return returnStr;
}

/**
 * Converts a double to string.
 * @param value The double to convert.
 * @return String representation of value.
 */
const char* StringHelper::dtos(double value){
    std::ostringstream sstream;
    sstream << value;
    const char* returnStr = write(sstream.str().c_str());
    return returnStr;
}

int StringHelper::stoi(const char* value){
    std::istringstream sstream(value);
    int ret;
    sstream >> ret;
    return ret;
}

/**
 * Concatenate given strings into one.
 */
const char* StringHelper::concat(int count, ...){
    if(count <= 1)
        return 0;

    va_list args;
    va_start(args, count);
    char* str1 = va_arg(args, char*);
    int len = strlen(str1) + 1;
    for(int i = 1; i < count; i++){
        char* str2 = va_arg(args, char*);
        len += strlen(str2);
    }
    va_end(args);

    char* returnStr = (char*)concatPool.allocate(len+1);
    if(len > STRING_LEN && returnStr){  
        return 0;
    }
    concatPool.clear();

    va_start(args, count);
    //Pop str1
    va_arg(args, char*);
    strcpy(returnStr, str1);
    for(int i = 1; i < count; i++){
        char* str2 = va_arg(args, char*);
        strcat(returnStr, str2);
    }

    returnStr[len] = 0;
    return returnStr;
}