#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <renderWindow.h>

renderWindow gameWindow;

bool gameRunning = 1;

int main (int argc, char **argv) {

    SDL_Init(SDL_INIT_VIDEO);

    gameWindow.createWindow("Test", 1280, 720);

    std::string basePath = std::string(SDL_GetBasePath());

    SDL_Texture* catImage = gameWindow.loadTexture((basePath + "data/images/cat.png").c_str());

    SDL_Event e;

    while (gameRunning) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                gameRunning = 0;
            }
        } 

        gameWindow.clearRenderer();
        gameWindow.renderTexture(catImage);
        gameWindow.displayTexture();
    }

    gameWindow.cleanUp();
    SDL_Quit();

    return 0;
}