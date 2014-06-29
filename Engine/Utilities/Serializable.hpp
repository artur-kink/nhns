#ifndef _SERIALIZABLE_
#define _SERIALIZABLE_

#ifdef _PC_
#include <iostream>
#include "Utilities/FileHandler.hpp"
#endif

#include "MemoryPool.hpp"
/**
 * Base class for objects that can be serialized.
 * A serialized object can be written to and read from a file.
 * The serialize function must be only implemented on _PC_ platform.
 */
class Serializable{
private:
    
public:
#ifdef _PC_
    /**
     * Serialize this object.
     * @param destination Destination file to serialize this object to.
     */
    virtual void serialize(std::ofstream& destination) = 0;
#endif
    /**
     * De-serialize this object.
     * @param source Memory pool location of serialized object.
     */
    virtual void deserialize(MemoryPool* source) = 0;
};

#endif