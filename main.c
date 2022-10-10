#if defined(_WIN32)
    #define SDL_MAIN_HANDLED
#endif

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int PlaySound(Mix_Chunk *wave);
Mix_Chunk LoadSound(char *wav_path);

void quit();
int init();

static Mix_Chunk waves[3];

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
SDL_Surface *screen = NULL;

int main(int argc, char **argv)
{
    if (init() == 1)
        return 1;

    SDL_Event e;

    bool run = true;

    while (run)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDL_SCANCODE_Q)
                        PlaySound(waves[0]);
                    if (e.key.keysym.sym == SDL_SCANCODE_W)
                        PlaySound(waves[1]);
                    if (e.key.keysym.sym == SDL_SCANCODE_E)
                        PlaySound(waves[2]);
                    break;
                default:
                    break;
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen -> format, 30, 30, 30));

        SDL_UpdateWindowSurface(window);
    }

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    quit();

    return 0;
}

int init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("Can't init: %s", SDL_GetError());
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

    waves[0] = LoadSound("Razor.wav");
    waves[1] = LoadSound("See Saw.wav");
    waves[2] = LoadSound("Sphere Hybrid.wav");

    return 0;
}

void quit()
{
    Mix_CloseAudio();
    Mix_Quit();

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

Mix_Chunk LoadSound(char wav_path[])
{
    Mix_Chunk *wave = Mix_LoadWAV(wav_path);
    return *wave;
}

void PlaySound(Mix_Chunk *wave)
{
    Mix_PlayChannel(-1, wave, 0);
        
    while (Mix_PlayingMusic());

    Mix_FreeChunk(wave);
}
