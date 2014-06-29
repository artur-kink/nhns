#ifndef _MESSAGEQUEUE_
#define _MESSAGEQUEUE_

#include "Utilities/MemoryPool.hpp"
#include "Utilities/Logger.hpp"

#include "Message.hpp"
#include "MessageIterator.hpp"

#ifdef _PC_
#include "SFML/Network.hpp"
#endif

/** 
* Queue of network messages.
* This class is responsible for parsing and creating network packets from
* lists of messages and sending these packets.
*/
class MessageQueue {
    friend class Message;
private:

    /** 
    * The length of a message cycle in milliseconds.
    */
    static const uint32_t MESSAGE_CYCLE_LENGTH = 100;

    /** 
    * The message queue must be sent immediately, instead of waiting for next message cycle.
    */
    bool forceSend;

    /** 
    * Message Cycle timer. Whenever timer overflows MESSAGE_CYCLE_LENGTH
    * the queue should send its messages.
    * Also counts the amount of time since last message sent.
    */
    sf::Clock cycleTimer;

	/** 
	* General begin() MessageIterator.
	*/
	MessageIterator messageIterator;
public:

	/** 
	* Abstract base class used to store server's time.
	*/
	class ServerTime {
    public:
        virtual uint32_t getTime() = 0;
    };

	static ServerTime* serverTime;

	static void initialize(ServerTime* getTimePointer);

	MemoryPool messagePool;

    /** 
    * Number of messages in queue.
    */
    uint16_t size;

    MessageQueue();
    MessageQueue(Message* message);

	MessageIterator& begin();
	MessageIterator& getFirstMessage(unsigned short code);

	MessageIterator& parse(unsigned short code, uint32_t serverTime, size_t bufferSize, void* buffer);
    MessageIterator& createMessage(unsigned short code, void* data);

#ifdef _PC_
    sf::Packet* getMessagePacket();

    sf::Socket::Status forceSendQueue(sf::UdpSocket& socket, const sf::IpAddress& address, const unsigned short& port);
    sf::Socket::Status sendQueue(sf::UdpSocket& socket, const sf::IpAddress& address, const unsigned short& port);

    void parsePacket(const sf::Packet& packet);
#endif

    void clearQueue();

    ~MessageQueue();
};

#endif