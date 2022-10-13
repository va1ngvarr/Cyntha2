#ifndef __UTILS_H__
#define __UTILS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "globals.h"

#pragma once
#ifdef __cplusplus

    #include <vector>

    extern "C"
    {
#endif
        void draw_rects();
        void PlaySound(int chunk);
        void LoadSound(const char *wav_path);

        void SetVolume(int vol);

        void CreateRect(int x, int y, int w, int h);

// C-Styled function prototypes

#ifdef __cplusplus
	}
#endif

static int volume;

#endif