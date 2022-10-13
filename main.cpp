#if defined(_WIN32)
    #define SDL_MAIN_HANDLED
#endif

#include "cyntha2.h"
#include "utils.h"

#include "globals.h"

char *paths[] = 
{
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Coco - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Razor - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Savage - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Talent - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura 808 - Vortex - C.wav",

    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Almost Strings - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Dark Reese 01 - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Dirty Clean - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - FM Donk - C.wav",
    "Sounds/Echo Sound Works - Aura One Shots/ESW Aura Bass - Medusa - C.wav"
};

int main(int argc, char **argv)
{
    if (init() == 1)
        return 1;

    SetVolume(50);

    for (int i = 0; i < sizeof(paths)/sizeof(paths[0]); i++)
        LoadSound(paths[i]);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen -> format, 30, 30, 30));

    SDL_Event e;
    bool run = true;

    SDL_KeyCode bindings[] = {SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t,
            SDLK_a, SDLK_s, SDLK_d, SDLK_f, SDLK_g};

    draw_rects();

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
                    draw_rects();
                    for (int i = 0; i < 10; i++)
                    {
                        if (e.key.keysym.sym == bindings[i])
                        {
                            SDL_SetRenderDrawColor(render, 255, 20, 20, 255);
                            if (i >= 5)
                                SDL_SetRenderDrawColor(render, 20, 255, 20, 255);
                            PlaySound(i);
                            SDL_RenderFillRect(render, &rects[i]);
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_RenderPresent(render);
    }

    quit();

    return 0;
}
