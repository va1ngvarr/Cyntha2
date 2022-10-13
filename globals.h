#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <vector>

extern SDL_Window *window;
extern SDL_Renderer *render;
extern SDL_Surface *screen;

extern std::vector<SDL_Rect> rects;
extern std::vector<Mix_Chunk*> chunks;

#endif
