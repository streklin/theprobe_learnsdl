#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#include <SDL_mixer.h>
#include <memory>

class AudioManager final {
public:
    AudioManager();     

    void loadMusicMedia(const std::string path);
    void play();
    void stop();
private:
    Mix_Music* _music;
};

#endif