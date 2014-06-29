#include "NetworkHandler.hpp"

NetworkHandler::NetworkHandler(){
    inPort = outPort = 50012;
}

/**
 * Bind the socket to the given address and port. Opens Socket.
 * @param addr Address to bind to.
 * @param port Port to bind to.
 */
void NetworkHandler::bind(const char* addr, unsigned short port){
    inPort = port;
    socket.unbind();
    socket.bind(inPort);
    socket.setBlocking(false);

    address = sf::IpAddress(addr);
}

/**
 * Set port for outgoing messages.
 * @param port Port to set.
 */
void NetworkHandler::setOutPort(unsigned short port){
    outPort = port;
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
    sf::IpAddress rAddress;
    unsigned short rPort;

    if(socket.receive(receivedPacket, rAddress, rPort) == sf::Socket::Done){
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
}