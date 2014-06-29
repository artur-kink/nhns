#ifndef _AUDIOMANAGER_
#define _AUDIOMANAGER_

#include <cstring>
#include "Utilities/ResourceManager.hpp"
#include "AudioObject.hpp"
#include "Utilities/KeyValuePair.hpp"

/**
 * Class used to load, manage and play Audio.
 */
class AudioManager:public ResourceManager{
private:

#ifdef _PC_
    /** Max number of concurrent sounds supported. */
    static const byte maxSounds = 10;
    /** SFML sound objects. */
    sf::Sound sounds[maxSounds];
    /** SFML music object for streamed music playback. */
    sf::Music music;
#endif

public:

    /** List of audio objects in audio manager. */
    AudioObject** audioObjects;

    /** Number of audio objects. */
    unsigned short objectCount;
    
    /** Index of audio object names */
    KeyValuePair<AudioObject>* audioNames;

    AudioManager();

    AudioObject* getAudioObject(const char* name);

    void play(const char* name);
    void play(AudioObject* object);
    void stopAll();

    virtual void load(const char* path);
#ifdef _PC_
    virtual void loadRaw(const char* file);
    virtual void save(const char* file);
#endif
    ~AudioManager();
};

#endif
