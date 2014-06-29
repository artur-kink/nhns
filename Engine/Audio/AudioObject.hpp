#ifndef _AUDIOOBJECT_
#define _AUDIOOBJECT_

#include "Types.hpp"
#include "Utilities/Serializable.hpp"

#ifdef _PC_
#include "SFML/Audio.hpp"
#endif

/**
 * Audio object used to store and play audio data.
 */
class AudioObject:public Serializable{
private:

public:
    /** 
    * Pointer to the name of the audio object.
    * Note that this pointer is shared with the audioObjectNames list
    * of AudioManager. The names are managed by the audio manager
    * and therefore this pointer should not be allocated or released.
    */
    char* name;

    /** Name of file where audio data is stored. */
    char* fileName;

    /** Index of this object in the AudioManager. */
    unsigned short index;

    /**
     * Type of audio object.
     */
    enum AudioType{
        /** Loaded and kept in memory. */
        at_Preloaded = 0,
        /** Loaded only when used, streamed on playback. */
        at_LoadOnUse = 1
    };

    /** AudioType of this object. */
    byte type;
#ifdef _PC_
    /** SFML sound buffer where audio data is stored. */
    sf::SoundBuffer soundBuffer;
#endif
    AudioObject();

#ifdef _PC_
    virtual void serialize(std::ofstream& destination);
#endif
    virtual void deserialize(MemoryPool* source);

    ~AudioObject();
};

#endif