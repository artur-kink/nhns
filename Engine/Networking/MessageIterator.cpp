#include "MessageIterator.hpp"

MessageIterator::MessageIterator(){
	position = 0;
	messagePool = 0;
	message = 0;
}

/** 
* MessageIterator copy constructor.
* @param other Copy source.
*/
MessageIterator::MessageIterator(const MessageIterator& other){
	position = other.position;
	messagePool = other.messagePool;
	message = other.message;
}

/** 
* Initializes the iterator for specified pool and parses first message in pool.
*/
void MessageIterator::init(MemoryPool* pool){
	position = 0;
	messagePool = pool;
	parseMessage();
}

/** 
* Sets the position of the iterator and parses message at given position.
*/
void MessageIterator::setPosition(unsigned int p){
	position = p;
	parseMessage();
}

/** 
* Parses Message at current position in pool. Increments position of pool to next message.
*/
void MessageIterator::parseMessage(){

	//Check that position in pool range.
	if(messagePool->eor()){
		message = 0;
		return;
	}

	//Check that the pool is not empty
	if(messagePool->getLength() != 0){
		//Get message code at position and parse message if possible.
		message = (Message*)(messagePool->getBuffer() + position);
		if(position + sizeof(Message) + Message::bufferSize(message->code) <= messagePool->getLength()){
			position += sizeof(Message) + Message::bufferSize(message->code);
		}
	}
}

/** 
* Clear iterator to point at nothing.
*/
void MessageIterator::clear(){
	message = 0;
	position = 0;
}

/** 
* Increments iterator to next Message.
*/
MessageIterator& MessageIterator::operator++() {
	parseMessage();
	return *this;
}

/** 
* Get this iterator's Message.
*/
Message* MessageIterator::operator*() {
	return message;
}