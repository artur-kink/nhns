#include "Networking/Networking.hpp"
#include "Utilities/LogManager.hpp"
#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/Logger.hpp"

int main(int argc, char** argv){
    StringHelper::init();

    Log >> new ConsoleLogger();
    Log.setLevelFilter(Logger::ll_Debug);

    NetworkHandler client;
    client.bind("localhost", 50013);
    client.setOutPort(50012);

    while(true){
        Log << LL_D << "Waiting for message from client.";
        MessageQueue* messages = client.getMessagesBlocking(500);
        if(messages){
            Log << LL_D << "Got messages.";
        }
    }
}
