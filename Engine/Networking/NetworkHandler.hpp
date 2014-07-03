#ifndef _NETWORKHANDLER_
#define	_NETWORKHANDLER_

#ifdef _PC_
#include <SFML/Network.hpp>
#endif

#include "MessageQueue.hpp"

/**
 * Interface class for a socket and its connection.
 * Handles opening/closing and sending messages between two connections.
 * The connection uses UDP.
 */
class NetworkHandler{
private:

#ifdef _PC_
    /** SFML specific connection address. */
    sf::IpAddress address;

    /** SFML specific socket implementation. */
    sf::UdpSocket socket;
#endif

    /** Port for incoming messages. */
    unsigned short inPort;
    /** Port for outgoing messages. */
    unsigned short outPort;

public:

    /** MessageQueue for outgoing messages. */
    MessageQueue outQueue;
    /** MessageQueue for received messages. */
	MessageQueue inQueue;

    /** Address of last received message. */
    char* lastMessageAddress;
    
    /** Port of last received message.*/
    unsigned short lastMessagePort;

    NetworkHandler();

    void bind(unsigned short port);
    void setOutConnection(const char* addr, unsigned short port);
    const char* getOutAddress();
    unsigned short getOutPort();

    MessageIterator& addMessage(unsigned short code, void* data);
    bool sendMessages();
    bool forceSendMessages();

    MessageQueue* getMessages();
    MessageQueue* getMessagesBlocking(unsigned int timeout);

    void close();


    ~NetworkHandler();
};

#endif