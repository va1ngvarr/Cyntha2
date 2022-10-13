#include <cstdio>

#include "cyntha2.h"

SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
SDL_Surface *screen = NULL;

std::vector<Mix_Chunk*> chunks;
std::vector<SDL_Rect> rects;

void CreateRect(int x, int y, int w, int h)
{
    SDL_Rect r = {x, y, w, h};

    rects.push_back(r);
}

void LoadSound(const char *wav_path)
{
    Mix_Chunk *chunk = NULL;
    chunk = Mix_LoadWAV(wav_path);

    chunks.push_back(chunk);
}

void PlaySound(int chunk)
{
    Mix_Volume(-1, volume);
    Mix_PlayChannel(-1, chunks[chunk], 0);
        
    while (Mix_PlayingMusic());
}

void SetVolume(int vol)
{
    volume = (MIX_MAX_VOLUME * vol) / 100;
}

int init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("Can't init: %s", SDL_GetError());
        return 1;
    }

    Mix_Init(MIX_INIT_MP3);

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    {
        printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Cyntha2", SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Can't create window: %s", SDL_GetError());
        return 1;
    }

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(window);

    return 0;
}

void quit()
{   
    for(int i = 0; i < chunks.size(); i++)
    {
        Mix_FreeChunk(chunks[i]);
        chunks[i] = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
