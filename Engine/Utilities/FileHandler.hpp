#ifndef _FILEHANDLER_
#define _FILEHANDLER_

#include "Types.hpp"
#include "LogManager.hpp"
#include "MemoryPool.hpp"

#ifdef _PC_
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#endif

/**
 * A File information data structure.
 */
struct File{
    friend class FileHandler;

protected:
#ifdef _PC_
    /** Data stream for file. Platform specific implementation. */
    std::fstream* fileStream;
#endif

public:
    /** Buffer of read data. */
    void* buffer;

    /** Size of buffer. */
    unsigned int bufferSize;

    /** Size of file in bytes. */
    unsigned int size;

    /** Position in file. */
    unsigned int pos;
};

/**
 * File handling utility.
 * Used for reading and writing files.
 */
class FileHandler{
public:
    /** File access modes. */
    enum FileAccessMode{
        fam_Read,
        fam_Write,
        fam_Append,
        fam_ReadWrite,
        fam_New
    };
private:

public:
    FileHandler();

    File openFile(const char* path, FileAccessMode mode);
    MemoryPool* readFile(const char* path);
    bool read(File& file, unsigned int length, void* buffer);
    bool write(File& file, unsigned int length, void* buffer);
    bool closeFile(File& file);
};

#endif