#include "Networking/Networking.hpp"
#include "Utilities/LogManager.hpp"
#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/Logger.hpp"

int main(int argc, char** argv){

    StringHelper::init();
    
    Log >> new ConsoleLogger();
    Log.setLevelFilter(Logger::ll_Debug);

    NetworkHandler client;
    client.bind("localhost", 50012);
    client.setOutPort(50013);

    while(true){
        Log << LL_D << "Pinging server.";

        client.addMessage(Message::m_b_Ping, 0);
        client.sendMessages();

        MessageQueue* messages = client.getMessagesBlocking(500);
        if(messages){
            Log << LL_D << "Got messages.";
        }
    }
}
