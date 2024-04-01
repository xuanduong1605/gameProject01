#include <bits/stdc++.h>
#include "SDL2/SDL.h"

int main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("Cant init sdl\n");
        exit(0);
    }
    SDL_Window *window = SDL_CreateWindow(
        "test sdl program",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        800,600,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
    );

    SDL_Delay(5000);
    return 0;
}