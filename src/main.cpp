#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int screenWidth = 1280;
const int screenHeight = 720;

SDL_Window* gameWindow = NULL;

SDL_Surface* gameScreenSurface = NULL;
SDL_Surface* backgroundImage = NULL;

SDL_Renderer* screenRenderer = NULL;


int main (int argc, char **argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("Can't init sdl\n");
        exit(0);
    }

    gameWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);

    screenRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    bool quitGame = 0;

    SDL_Event e;

    while (!quitGame) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quitGame = 1;
            }

            SDL_SetRenderDrawColor(screenRenderer,0,0,0,0);
            SDL_RenderClear(screenRenderer);

            SDL_SetRenderDrawColor(screenRenderer,255,0,0,255);
            SDL_RenderDrawLine(screenRenderer,20,20,50,50);

            SDL_Rect rect = {50,50,100,200};
            SDL_SetRenderDrawColor(screenRenderer,0,255,0,255);
            SDL_RenderFillRect(screenRenderer,&rect);

            SDL_RenderPresent(screenRenderer);
            SDL_Delay(20);
        }
    }
    return 0;
}