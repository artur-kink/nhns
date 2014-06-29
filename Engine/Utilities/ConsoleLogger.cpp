#include "ConsoleLogger.hpp"

ConsoleLogger::ConsoleLogger(){

}

void ConsoleLogger::write(const char* str){

    //Write newline if this is a new log entry.
    if(isNewCall){
        isNewCall = false;
        write("\n");
    }
#ifdef _PC_
    std::cout << str;
#endif
}

void ConsoleLogger::newCall(){
    isNewCall = true;
}