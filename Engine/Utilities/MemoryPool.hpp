#ifndef _MEMORYPOOL_
#define _MEMORYPOOL_

#include "Types.hpp"

#ifdef _PC_
#include <cstring>
#endif

/** 
 * Basic memory pool that can only grow or be cleared.
 * Allocations can vary in size.
 */
class MemoryPool{
private:
    /** Size of memory pool in bytes. */
    unsigned int size;

    /** Memory pool buffer. */
    byte* pool;

    /** Previous location of memory pool that has been allocated to. */
    unsigned int lastLocation;

    /** Current location of memory pool that is free. */
    unsigned int location;

    /** Current location where the pool is being read. */
    unsigned int readLocation;

    /** Should the values being read be read in reverse(Switch endianness). */
    bool reverseEndian;
public:

    MemoryPool();
    MemoryPool(unsigned int s);

    void setBuffer(void* buffer, unsigned int s);
    byte* getBuffer();

    void createPool(unsigned int s);
    void* allocate(unsigned int as);
    unsigned int getLength();
    unsigned int getMemoryLeft();

    bool copyToPool(unsigned int s, void* src);
    
    bool read(void* dst, unsigned int s);
    bool read(void* dst, unsigned int s, unsigned int pos, bool reverse);
    bool readString(char* dst, unsigned int s);
    bool readString(char* dst);
    bool eor();

    void readAsReverseEndian();

    void setLocation(unsigned int loc);
    void clear();
    void erase();

    ~MemoryPool();
};

#endif