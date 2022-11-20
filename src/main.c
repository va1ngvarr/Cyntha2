#if defined(_WIN32)
    #define SDL_MAIN_HANDLED
    /*      ~~~~~~~~~~~~~~~~ 
     * This is necessary for the program can run on Windows
     * Because SDL uses WINAPI for Windows
     * Without this code, the WinMain function is needed, but it may not work
     */
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>
#include <stdio.h>

#include "structs.h"

#define BUTTONS_AMOUNT sizeof(wav_paths)/sizeof(wav_paths[0])

const Uint16 SCREEN_WIDTH = 600;
const Uint16 SCREEN_HEIGHT = 400;

const char *wav_paths[] = 
{
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Coco - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Razor - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Savage - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Talent - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Vortex - C.wav",

    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Almost Strings - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Dark Reese 01 - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Dirty Clean - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - FM Donk - C.wav",
    "resources/Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Medusa - C.wav"
};

Button buttons[BUTTONS_AMOUNT];

Mix_Chunk *chunks[BUTTONS_AMOUNT];

void LoadSound(const char *wav_path);
void PlaySound(Mix_Chunk *chunk);
void SetVolume(Uint8 vol);

void DrawSquare(SDL_Renderer *renderer, SDL_Rect rect, RGB rgb);
void CreateButton(Mix_Chunk *chunk, Pos_Size PosSize, SDL_KeyCode key_bind, RGB PassiveRGB, RGB ActiveRGB, int Index);

int init();
void quit();

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Surface *screen = NULL;

static Uint8 volume;

const SDL_KeyCode bindings[] = 
{
    SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t,
    SDLK_a, SDLK_s, SDLK_d, SDLK_f, SDLK_g
};

int main(int argc, char **argv)
{
    if (init() == 1) // Initialization SDL2, SDL2_Mixer
        return 1;

    SDL_SetRenderDrawColor(renderer, 50, 25, 40, 255);
    SDL_RenderClear(renderer);

    RGB rgbs[2][2] = 
    {
        {
            {30, 200, 30, 255},
            {200, 30, 30, 255}
        },

        {
            {20, 255, 20, 255},
            {255, 20, 20, 255}
        }
    };

    int ratio[] = {1, 5}; // padding to button size ratio

    Uint16 sqr_pad;
    Uint16 sqr_side;
    
    int row = 5; // number of buttons per row

    // margins and button sizes depend on screen width

    sqr_pad  = SCREEN_WIDTH / (row+1) / (ratio[0] + ratio[1]) * ratio[0];
    sqr_side = SCREEN_WIDTH / row / (ratio[0] + ratio[1]) * ratio[1];

    Pos_Size PosSize = {sqr_pad, sqr_pad, sqr_side, sqr_side};

    for (int i = 0; i < BUTTONS_AMOUNT; i++)
    {
        LoadSound(wav_paths[i]);

        if (i > 4) // Second row is green
        {
            CreateButton(chunks[i], PosSize, bindings[i], rgbs[0][0], rgbs[1][0], i);
        }
        else
            CreateButton(chunks[i], PosSize, bindings[i], rgbs[0][1], rgbs[1][1], i);

        // Update position
        PosSize.x += sqr_pad + sqr_side;

        if (i == 4) // Second row
        {
            PosSize.x = sqr_pad;
            PosSize.y += sqr_pad + sqr_side;
        }

        // Rendering
        DrawSquare(renderer, buttons[i].rect, buttons[i].PassiveRGB);
    }

    SDL_Event e;

    bool loop = true;

    while (loop)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    loop = false;
                    break;

                case SDL_KEYDOWN:
                    for (int i = 0; i < BUTTONS_AMOUNT; i++)
                    {
                        if (e.key.keysym.sym == buttons[i].key_bind)
                        {
                            PlaySound(buttons[i].chunk);
                            buttons[i].Clicked = 1;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < BUTTONS_AMOUNT; i++)
                    {
                        if ((e.button.x > buttons[i].rect.x) && (e.button.x < buttons[i].rect.x + buttons[i].rect.w) &&
                            (e.button.y > buttons[i].rect.y) && (e.button.y < buttons[i].rect.y + buttons[i].rect.h))
                        {
                            PlaySound(buttons[i].chunk);
                            buttons[i].Clicked = 1;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    quit(); // Deinitialization SDL, unloading waves

    return 0;
}

void LoadSound(const char *wav_path)
{
    Mix_Chunk *chunk = Mix_LoadWAV(wav_path);

    for (int i = 0; i < BUTTONS_AMOUNT; i++)
    {
        if (chunks[i] == NULL)
        {
            chunks[i] = chunk;
            break;
        }
    }
}

void PlaySound(Mix_Chunk *chunk)
{
    Mix_PlayChannel(-1, chunk, 0);
}

void SetVolume(Uint8 vol)
{
    volume = (MIX_MAX_VOLUME * vol) / 100;
    Mix_Volume(-1, vol);
}

void DrawSquare(SDL_Renderer *renderer, SDL_Rect rect, RGB rgb)
{
    SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);
    SDL_RenderFillRect(renderer, &rect);
}

void CreateButton(Mix_Chunk *chunk, Pos_Size PosSize, SDL_KeyCode key_bind, RGB PassiveRGB, RGB ActiveRGB, int Index)
{
    SDL_Rect rect = {PosSize.x, PosSize.y, PosSize.w, PosSize.h};
    Button button = {chunk, rect, key_bind, PassiveRGB, ActiveRGB, false};

    buttons[Index] = button;
}

int init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        printf("Can't init: %s", SDL_GetError());
        return 1;
    }

    if (!Mix_Init(MIX_INIT_MP3))
    {
        printf("SDL_Mixer couldn't init. Err: %s", Mix_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    {
        printf("Mix_OpenAudio not created. Err: %s\n", Mix_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Cyntha2", SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Can't create window: %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Can't create renderer: %s", SDL_GetError());
        return 1;
    }

    screen = SDL_GetWindowSurface(window);

    SetVolume(50);

    return 0;
}

void quit()
{   
    for(int i = 0; i < BUTTONS_AMOUNT; i++)
    {
        Mix_FreeChunk(chunks[i]);
        chunks[i] = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
