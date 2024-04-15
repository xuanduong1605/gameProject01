#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector2d.h>
#include <entity.h>
#include <renderWindow.h>

renderWindow gameWindow;

bool gameRunning = 1;

int main (int argc, char **argv) {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    gameWindow.createWindow("Test", 1280, 720);

    std::string basePath = std::string(SDL_GetBasePath());

    SDL_Texture* ball = gameWindow.loadTexture((basePath + "data/images/ball.png").c_str());

    Entity Ball (Vector2d(100, 50), ball);

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