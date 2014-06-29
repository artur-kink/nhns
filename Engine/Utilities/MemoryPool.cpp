#include "MemoryPool.hpp"

/** 
* Initializes an empty, 0 byte pool.
*/
MemoryPool::MemoryPool(){
	location = 0;
	lastLocation = 0;
	size = 0;
    readLocation = 0;
    reverseEndian = false;
}

/**
 * Initialize a pool of size s.
 */
MemoryPool::MemoryPool(unsigned int s){
    createPool(s);
    reverseEndian = false;
}

/**
 * Set the buffer of the memory pool, this should only be used if
 * the pool buffer has been created by something other than
 * the MemoryPool. Note that the buffer memory will be deleted
 * by the memory pool, thus the memory should not be cleared
 * or the buffer should be set to a null pointer before the
 * memory pool is destroyed.
 * @param buffer Address to buffer to be used.
 * @param s Size of buffer in bytes.
 */
void MemoryPool::setBuffer(void* buffer, unsigned int s){
    size = s;
    pool = (byte*)buffer;
}

/**
 * Get direct access to pool buffer.
 * This should be used with extreme care.
 */
byte* MemoryPool::getBuffer(){
    return pool;
}

/** 
* Create memory pool of size s bytes.
* @param s Size of pool in bytes.
*/
void MemoryPool::createPool(unsigned int s){
	size = s;
	pool = new byte[size];
    clear();
}

/** 
* Allocates as bytes in the pool.
* @param as Number of bytes to allocate.
* @return Pointer to beginning of allocated memory, or 0 if failed.
*/
void* MemoryPool::allocate(unsigned int as){
	//Check if we have enough space for this allocation.
	if(location + as >= size){
		return 0;
	}
	
	lastLocation = location;
	location += as;
	return (pool + (lastLocation));
}

/**
 * Get the number of unallocated bytes left in the pool.
 * A number larger than the size of the pool implies
 * that an error has occured.
 */
unsigned int MemoryPool::getMemoryLeft(){
    return size - location;
}

/**
 * Get the length in bytes of memory written to the pool.
 */
unsigned int MemoryPool::getLength(){
    return location;
}

/**
 * Copy s bytes from src to the pool.
 * @param s Size in bytes.
 * @param src Data to copy.
 * @return true if copy succeeded, false otherwise.
 * @see MemoryPool::read To copy data from pool.
 */
bool MemoryPool::copyToPool(unsigned int s, void* src) {
	void* allocatedLocation = allocate(s);
    if (!allocatedLocation){
	    return false;
	}
#ifdef _PC_
	memcpy(allocatedLocation, src, s);
#endif
    return true;
}

/** 
 * Read data from pool into given destination.
 * @param dst Address to copy data into.
 * @param s Number of bytes to read.
 * @return true on success, false otherwise.
 */
bool MemoryPool::read(void* dst, unsigned int s){
    bool ret = read(dst, s, readLocation, reverseEndian);
    readLocation += s;
    return ret;
}

/**
 * Read data from pool at given position.
 * @param dst Address to copy data into.
 * @param s Number of bytes to read.
 * @param pos Position to start reading at.
 * @param reverse Should data be read in reverse order.
 * If data is currently in little endian then read as big endian. If
 * data is in big endian then read as little endian.
 * @return true on success, false otherwise.
 */
bool MemoryPool::read(void* dst, unsigned int s, unsigned int pos, bool reverse){
    if(pos + s > location)
        return false;

    if(reverse){
    #ifdef _PC_
        for(unsigned int i = 0; i < s; i++){
            memcpy((void*)((byte*)dst + i), (void*)(pool + pos + (s - i - 1)), 1);
        }
    #endif
    }else{
#ifdef _PC_
        memcpy(dst, (void*)(pool + pos), s);
#endif
    }
    return true;
}

/**
 * Read a string from the pool.
 * @param dst Destination to read string into.
 * @param s Length of string.
 * @return true on success, false on failure.
 */
bool MemoryPool::readString(char* dst, unsigned int s){
    bool ret = read(dst, s, readLocation, false);
    readLocation += s;
    //Ensure null terminator
    dst[s] = 0;
    return ret;
}

/**
 * Read a string from the pool, Reads until reaches a
 * string terminator.
 * non-ascii characters.
 */
bool MemoryPool::readString(char* dst){
    //Figure out string length.
    unsigned int len = 0;
    int loc = readLocation;
    while((loc < location) && pool[loc] != 0){
        loc++;
    }
    if(pool[loc] == 0)
        loc++;

    //Read the string.
    return readString(dst, loc - readLocation);
}

/**
 * End of Read; Has the read reached end of buffer.
 */
bool MemoryPool::eor(){
    return (readLocation >= location);
}

/**
 * Set all non string read operations to read in reverse
 * in order to switch endianness. If data in pool is in
 * little endian then read as big endian, likewise with
 * big endian.
 */
void MemoryPool::readAsReverseEndian(){
    reverseEndian = true;
}

/**
 * Set the location of the pool where it is free.
 * Use with care.
 * @param loc Location to set. Has to be between zero
 * and size to avoid crash.
 */
void MemoryPool::setLocation(unsigned int loc){
    location = loc;
}

/** 
 * Clears the pool by resetting position to 0.
 * This method does not actually delete the pool memory.
 */
void MemoryPool::clear(){
	location = 0;
	lastLocation = 0;
    readLocation = 0;
}

/**
 * Deletes the memory pool buffer from memory and resets all positions to 0.
 * MemoryPool cannot be used again unless createPool is first called.
 */
void MemoryPool::erase(){
    if(size != 0){
		delete pool;
		size = 0;
		pool = 0;
	}
    clear();
}

/** 
 * Clears memory pool buffer from memory.
 */
MemoryPool::~MemoryPool(){
	erase();
}