#ifndef __STRUCT_H__
    #define __STRUCT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct
{
    Uint8 r, g, b, a;
} RGB;

typedef struct
{
    Uint16 x, y, w, h;
} Pos_Size;

typedef struct
{
    Mix_Chunk *chunk;
    SDL_Rect rect;

    SDL_KeyCode key_bind;

    RGB PassiveRGB;
    RGB ActiveRGB;

    bool Clicked;

} Button;

#endif // __STRUCT_H__