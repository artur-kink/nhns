#include "NetworkHandler.hpp"

NetworkHandler::NetworkHandler(){
    inPort = outPort = 50012;
    lastMessageAddress = new char[20];
}

/**
 * Bind the socket to the given port. Opens Socket to listen
 * to connections on given port.
 * @param port Port to bind to.
 */
void NetworkHandler::bind(unsigned short port){
    inPort = port;
    socket.unbind();
    socket.bind(inPort);
    socket.setBlocking(false);
}

/**
 * Set outgoing connection info.
 * @param addr Address to send to.
 * @param port Port to send to.
 */
void NetworkHandler::setOutConnection(const char* addr, unsigned short port){
    address = addr;
    outPort = port;
}

const char* NetworkHandler::getOutAddress(){
#ifdef _PC_
    return address.toString().c_str();
#endif
}

unsigned short NetworkHandler::getOutPort(){
    return outPort;
}

/**
 * Add message to send.
 * @param code Message code.
 * @param data Message data.
 * @return Iterator pointing to position of added message.
 */
MessageIterator& NetworkHandler::addMessage(unsigned short code, void* data){
	return outQueue.createMessage(code, data);
}

/**
 * Send any messages in the queue if they are ready to be sent.
 */
bool NetworkHandler::sendMessages(){
#ifdef _PC_
    if(outQueue.sendQueue(socket, address, outPort) == sf::Socket::Done){
        return true;
    }else{
        return false;
    }
#endif
}

/**
 * Force send any messages in the queue.
 */
bool NetworkHandler::forceSendMessages(){
#ifdef _PC_
    if(outQueue.forceSendQueue(socket, address, outPort) == sf::Socket::Done){
        return true;
    }else{
        return false;
    }
#endif
}

/**
 * Get messages from server.
 * @return MessageQueue with any messages received or 0 if none received.
 */
MessageQueue* NetworkHandler::getMessages(){
#ifdef _PC_
    sf::Packet receivedPacket;
    
    sf::IpAddress address;

    if(socket.receive(receivedPacket, address, lastMessagePort) == sf::Socket::Done){
        std::strcpy(lastMessageAddress, address.toString().c_str());
		inQueue.parsePacket(receivedPacket);
        return &inQueue;
    }
    return 0;
#endif
}

/**
 * A blocking call to get messages from server. Waits for specified time.
 * @param timeout Blocking call timeout time.
 * @todo Remove sf::Clock usage.
 */
MessageQueue* NetworkHandler::getMessagesBlocking(unsigned int timeout){
#ifdef _PC_
    sf::Clock timer;
    timer.restart();
    MessageQueue* returnQueue = getMessages();

	//Attempt reading messages until timeout reached or a message received.
    while (timer.getElapsedTime().asMilliseconds() < timeout && returnQueue == 0) {
        sf::sleep(sf::milliseconds(1));
        returnQueue = getMessages();
    }
    return returnQueue;
#endif
}

/**
 * Close connection with server.
 */
void NetworkHandler::close() {
    socket.unbind();
}

/**
 * Attempts to close connection.
 */
NetworkHandler::~NetworkHandler() {
    close();
    delete lastMessageAddress;
    lastMessageAddress = 0;
}