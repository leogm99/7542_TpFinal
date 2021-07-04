//
// Created by leogm99 on 4/7/21.
//

#ifndef SDLSOUND_H
#define SDLSOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>

class SdlSound {
private:
    Mix_Chunk* effect;
public:
    explicit SdlSound(const std::string& soundPath);

    SdlSound(const SdlSound& other) = delete;
    SdlSound& operator=(const SdlSound& other) = delete;

    SdlSound(SdlSound&& other) noexcept;
    SdlSound& operator=(SdlSound&& other) noexcept;

    // reproduce con cierto volumen
    // en un canal habilitado
    int play();

    ~SdlSound();
};


#endif