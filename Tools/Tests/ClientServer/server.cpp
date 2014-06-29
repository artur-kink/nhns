#include "Networking/Networking.hpp"
#include "Utilities/LogManager.hpp"
#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/Logger.hpp"

int main(int argc, char** argv){
    StringHelper::init();

    Log >> new ConsoleLogger();
    Log.setLevelFilter(Logger::ll_Debug);

    NetworkHandler network;
    network.bind("localhost", 50013);
    network.setOutPort(50012);

    while(true){
        Log << LL_D << "Waiting for message from client.";
        MessageQueue* messages = network.getMessagesBlocking(500);
        if(messages){
            Log << LL_D << "Got " << messages->size << " messages.";

            for(MessageIterator message = messages->begin(); *message; ++message){
                if((*message)->code == Message::m_b_Ping){
                    Log << LL_D << "Got Ping message. Responding...";
                    network.addMessage(Message::m_b_Ping, 0);
                    network.sendMessages();
                }else {
                    Log << LL_D << "Got unexpected message.";
                }
            }
        }
    }
}
