#include "MessageQueue.hpp"

MessageQueue::ServerTime* MessageQueue::serverTime = 0;

/** 
* Initializes global MessageQueue ServerTime.
* @param getTimePointer The get time pointer.
*/
void MessageQueue::initialize(ServerTime* getTimePointer){
    serverTime = getTimePointer;
}

/** 
* Initializes a new instance of the MessageQueue class.
* @see MessageQueue
*/
MessageQueue::MessageQueue(){
    size = 0;
    forceSend = false;

    cycleTimer.restart();
	
	messagePool.createPool(5120);
	messageIterator.messagePool = &messagePool;
}

/** 
* Initializes a new instance of the MessageQueue class with an initial <see cref="Message" />.
* @param message Initial Message to add.
*/
MessageQueue::MessageQueue(Message* message){
    MessageQueue();
}

/** 
* Get a MessageIterator pointing at the first message in queue.
*/
MessageIterator& MessageQueue::begin(){
	messageIterator.init(&messagePool);
	return messageIterator;
}

#ifdef _PC_

/** 
* Puts all messages in queue into packet.
* @return Packet with all messages to be sent.
*/
sf::Packet* MessageQueue::getMessagePacket(){
	if(!messagePool.eor()){
        sf::Packet* packet = new sf::Packet;
        packet->append(&size, sizeof(uint16_t));

        for(MessageIterator message = begin(); *message; ++message){
            packet->append(&(*message)->code, sizeof(byte));
            packet->append(&(*message)->serverTime, sizeof((*message)->serverTime));
			packet->append((*message)->buffer, Message::bufferSize((*message)->code));
        }
        return packet;
    }else{
        return 0;
    }
}
#endif

/** 
* Return iterator positioned to the first message in the queue with the given code.
*/
MessageIterator& MessageQueue::getFirstMessage(unsigned short code){
    for(messageIterator = begin(); *messageIterator; ++messageIterator){
		if((*messageIterator)->code == code)
			break;
    }
	return messageIterator;
}

#ifdef _PC_

/** 
* Sends the queue to the specified address.
* @param socket Socket to send from.
* @param address Address to send to.
* @param port Port to send to.
*/
sf::Socket::Status MessageQueue::forceSendQueue(sf::UdpSocket& socket, const sf::IpAddress& address, const unsigned short& port){
    /*if(size != 0){
        sf::Packet* sendPacket = getMessagePacket();
        if(sendPacket != 0){
            sf::Socket::Status sendStatus = socket.send((*sendPacket), address, port);
            delete sendPacket;

            if(sendStatus == sf::Socket::Done){
                clearQueue();
                cycleTimer.restart();
            }
            return sendStatus;
        }
        delete sendPacket;
        return sf::Socket::Error;
    }
    return sf::Socket::Done;*/
}

/** 
* Sends the queue if cycle time has elapsed or queue is on forceSend
* If the queue is not sent because its not ready, Done is returned, else the socket response is sent.
* @return Socket's send return or Done if message not sent.
*/
sf::Socket::Status MessageQueue::sendQueue(sf::UdpSocket& socket, const sf::IpAddress& address, const unsigned short& port){
    /*if(cycleTimer.getElapsedTime().asMilliseconds() >= MESSAGE_CYCLE_LENGTH || forceSend){
        return forceSendQueue(socket, address, port);
    }
    return sf::Socket::Done;*/
}

/** 
* Parse a network packet into this queue.
*/
void MessageQueue::parsePacket(const sf::Packet& packet){
	clearQueue();
    //There can be no valid packet of less than this size
    if(packet.getDataSize() < MIN_PACKET_SIZE){
        return;
    }

    size_t byteCounter = 0;
    byte* data = (byte*) packet.getData();
    uint16_t messageCount = *(uint16_t*) data;

    data = data + sizeof(messageCount);
    byteCounter += sizeof(messageCount);

    for(unsigned int m = 0; m < messageCount; m++){
        byteCounter += sizeof(byte);
        byteCounter += sizeof(uint32_t);

        //Check if size is large enough for safe parsing.
        if(byteCounter > packet.getDataSize()){
            return;
        }

		//Get standard message information
        Message::MessageCode code = (Message::MessageCode)(*(byte*)data);
        data = data + sizeof(byte);

		//Check for valid code
		if(code >= Message::m_NUM_MESSAGES){
			Log << "Invalid code, discarding message.";
			break;
		}

        uint32_t serverTime = 0;
        serverTime = *(uint32_t*) data;
        data = data + sizeof(serverTime);

        size_t bufferSize = Message::bufferSize((unsigned short)code);

		//Check if size is large enough for safe parsing.
        if(byteCounter + bufferSize > packet.getDataSize()){
            return;
        }
		
        if(*parse(code, serverTime, bufferSize, data) == 0)
			return;

		byteCounter += bufferSize;
        data = data + bufferSize;
    }

}


#endif

/** 
* Creates message with given code and parses buffer into it.
* @return Returns empty iterator on fail, iterator pointing at message on success.
*/
MessageIterator& MessageQueue::parse(unsigned short code, uint32_t serverTime, size_t bufferSize, void* buffer){
	return createMessage(code, buffer);
}

/** 
* Create a message with given code and data.
* @param code Message code.
* @param data Pointer to message data.
* @return Iterator pointing at created message. Empty iterator on failure.
*/
MessageIterator& MessageQueue::createMessage(unsigned short code, void* data){

	//Allocate space in memory pool
	uint16_t bufferSize = Message::bufferSize((byte)code);
	Message* message = (Message*)messagePool.allocate(sizeof(Message) + bufferSize);
	if(message == 0){
		messageIterator.clear();
		return messageIterator;
	}

	//Copy message info
	message->code = code;
	message->group = (Message::MessageGroup)Message::messageGroup((byte)code);
	message->serverTime = serverTime->getTime();
	message->buffer = ((byte*)message) + sizeof(Message);

	//Copy data into buffer if any exists.
	if(bufferSize > 0){
		memcpy(message->buffer, data, bufferSize);
	}else{
		message->buffer = 0;
	}

	if(message->group == Message::g_Critical)
		forceSend = true;

	//Setup and return iterator.
	messageIterator.setPosition(messagePool.getLength() - messagePool.getMemoryLeft());
	size++;
	return messageIterator;
}

/** 
* Clears the queue.
*/
void MessageQueue::clearQueue(){
    size = 0;
	messagePool.clear();
    forceSend = false;
}

/** 
* MessageQueue destructor, clears all messages.
*/
MessageQueue::~MessageQueue(){
    clearQueue();
}