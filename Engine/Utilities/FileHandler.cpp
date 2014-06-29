#include "FileHandler.hpp"

FileHandler::FileHandler(){
}

/**
 * Open file at given path.
 */
File FileHandler::openFile(const char* path, FileAccessMode mode){
    Log << LL_D << LC_F << "Opening file: " << path;
#ifdef _PC_
    File file;
    
    bool newFile = false;
    std::ios::openmode m;
    switch(mode){
        case FileHandler::fam_Read:
            m = std::ios::in | std::ios::binary; break;
        case FileHandler::fam_Write:
            m = std::ios::out | std::ios::binary; break;
        case FileHandler::fam_Append:
            m = std::ios::out | std::ios::app | std::ios::binary; break;
        case FileHandler::fam_ReadWrite:
            m = std::ios::in | std::ios::out; break;
        case FileHandler::fam_New:
            m =  std::ios::out | std::ios::app | std::ios::binary; newFile = true; break;
    }

    if(!newFile){
        struct stat fileStat;
        int result = stat(path, &fileStat);
        if(result){
            return file;
        }
        file.size = fileStat.st_size;
        file.fileStream = new std::fstream();
        file.fileStream->open(path, m);
    }else{
        file.size = 0;
        file.fileStream = new std::fstream(path, m);
    }

    return file;
#endif
}

/**
 * Read all data in a file at given path.
 * This method allocates the required memory by itself,
 * however, the returned MemoryPool must be deleted by the user.
 * @param path Path of file to read.
 * @return Pointer to a MemoryPool which contains entire file content.
 */
MemoryPool* FileHandler::readFile(const char* path){

#ifdef _PC_
    File file = openFile(path, FileHandler::fam_Read);
    MemoryPool* pool = new MemoryPool(file.size);
    file.buffer = pool->getBuffer();

    bool result = read(file, file.size, file.buffer);
    if(!result){
        pool->erase();
    }else{
        pool->setLocation(file.size);
    }
    closeFile(file);
    return pool;
#endif
}

/**
 * Read data from an open file.
 * @param file File info struct.
 * @param length Length of data to read in bytes.
 * @param buffer Address to read into. This address must be initialized with proper length.
 * @return true if read succeeded, false otherwise.
 */
bool FileHandler::read(File& file, unsigned int length, void* buffer){
#ifdef _PC_
    file.fileStream->read((char*)buffer, length);
    return file.fileStream->good();
#endif
}

/**
 * Write to an open file.
 * @param file File info struct.
 * @param length Length of data to write in bytes.
 * @param buffer Address of data to write.
 * @return true if write succeeded, false otherwise.
 */
bool FileHandler::write(File& file, unsigned int length, void* buffer){
#ifdef _PC_
    file.fileStream->write((char*)buffer, length);
    file.fileStream->flush();
    return file.fileStream->fail();
#endif
}

/**
 * Close file.
 * @param file Reference to file to close.
 * @return true if succeeded, false otherwise.
 */
bool FileHandler::closeFile(File& file){
#ifdef _PC_
    if(file.fileStream->is_open()){
        file.fileStream->flush();
        file.fileStream->close();
    }else{
        Log << LL_W << LC_F << "Could not close file, File already closed.";
    }
    delete file.fileStream;
    return true;
#endif
}
