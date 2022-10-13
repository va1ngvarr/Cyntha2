#ifndef __CYNTHA2_H__
#define __CYNTHA2_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <vector>

#pragma once
#ifdef __cplusplus
	extern "C"
		{
#endif

// C-Style function prototypes

#ifdef __cplusplus
		}
#endif

void PlaySound(int chunk);
void LoadSound(const char *wav_path);

void CreateRect(int x, int y, int w, int h);

int init();
void quit();

void SetVolume(int vol);

static int volume;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#endif
