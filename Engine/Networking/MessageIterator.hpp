#ifndef _MESSAGEITERATOR_
#define _MESSAGEITERATOR_
#include <iterator>
#include "Message.hpp"
#include "Utilities/MemoryPool.hpp"

/** 
* An iterator over Messages in a MemoryPool.
*/
class MessageIterator:public std::iterator<std::forward_iterator_tag, Message*>{
	friend class MessageQueue;
protected:
	/** 
	* The message pool of the iterator.
	*/
	MemoryPool* messagePool;

	/** 
	* Byte position of the iterator.
	*/
	unsigned int position;

	/** 
	* Message the iterator is currently on.
	*/
	Message* message;

	void init(MemoryPool* pool);
	void parseMessage();
	void setPosition(unsigned int p);
	void clear();
public:

	MessageIterator();
	MessageIterator(const MessageIterator& other);
	MessageIterator& operator++();
	Message* operator*();
};

#endif