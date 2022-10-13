#include "utils.h"

std::vector<Mix_Chunk*> chunks;
std::vector<SDL_Rect> rects;

void CreateRect(int x, int y, int w, int h)
{
    SDL_Rect r = {x, y, w, h};

    rects.push_back(r);
}

void draw_rects()
{
    SDL_SetRenderDrawColor(render, 180, 20, 20, 255);

    int x = 20, y = 20, w = 103, h = 103;

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            x = 20;
            y = h + (y * 2);

            SDL_SetRenderDrawColor(render, 20, 180, 20, 255);
        }

        CreateRect(x, y, w, h);
        SDL_RenderFillRect(render, &rects[i]);
        x += 20 + w;
    }
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
