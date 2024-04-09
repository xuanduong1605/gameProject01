#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <renderWindow.h>

renderWindow gameWindow;

bool gameRunning = 1;

int main (int argc, char **argv) {

    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "Video failed to init. Error: " << SDL_GetError() << '\n';
    }

    gameWindow.createWindow("Test", 1280, 720);

    SDL_Event e;

    while (gameRunning) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                gameRunning = 0;
            }
        } 
    }

    gameWindow.cleanUp();
    SDL_Quit();

    return 0;
}