#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#include "AudioManager.h"

AudioManager::AudioManager() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        std::cout << "Unable to Initialize SDL_Mixer Error: " << Mix_GetError() << std::endl;
    }
}

void AudioManager::loadMusicMedia(const std::string path) {
    _music = Mix_LoadMUS(path.c_str());
}

void AudioManager::play() {
    Mix_PlayMusic(_music, -1);
}

void AudioManager::stop() {
    Mix_HaltMusic();
}