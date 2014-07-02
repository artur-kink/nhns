#include "Networking/Networking.hpp"
#include "Utilities/LogManager.hpp"
#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/Logger.hpp"

int main(int argc, char** argv){

    StringHelper::init();
    
    Log >> new ConsoleLogger();
    Log.setLevelFilter(Logger::ll_Debug);

    NetworkHandler network;
    network.bind(50012);
    network.setOutConnection("localhost", 50013);

    while(true){
        Log << LL_D << "Pinging server.";

        network.addMessage(Message::m_b_Ping, 0);
        network.sendMessages();

        MessageQueue* messages = network.getMessagesBlocking(500);
        if(messages){
            Log << LL_D << "Got " << messages->size << " messages.";

            for(MessageIterator message = messages->begin(); *message; ++message){
                if((*message)->code == Message::m_b_Ping){
                    Log << LL_D << "Got Ping message.";
                }else {
                    Log << LL_D << "Got unexpected message.";
                }
            }
        }
#ifdef _PC_
        sf::sleep(sf::milliseconds(1000));
#endif
    }
}
