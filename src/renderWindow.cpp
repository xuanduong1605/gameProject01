#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <renderWindow.h>
#include <entity.h>

renderWindow::renderWindow () {

}

void renderWindow::createWindow (const char *_Title, int _Width, int _Height) {
    gameWindow = SDL_CreateWindow(_Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _Width, _Height, SDL_WINDOW_SHOWN);

    if (gameWindow == NULL) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << '\n';
    }

    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
}

void renderWindow::cleanUp () {
    SDL_DestroyWindow(gameWindow);
}

void renderWindow::clearRenderer () {
    SDL_RenderClear(gameRenderer);
}

SDL_Texture *renderWindow::loadTexture (const char *_filePath) {
    SDL_Texture *currentTexture = NULL;
    currentTexture = IMG_LoadTexture(gameRenderer, _filePath);

    if (currentTexture == NULL) {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << '\n';
    }

    return currentTexture;
}

void renderWindow::renderTexture (Entity _Entity) {
    SDL_Rect startPos;
    startPos.x = _Entity.getFrame().x;
    startPos.y = _Entity.getFrame().y;
    startPos.w = 50;
    startPos.h = 50;

    SDL_Rect destinationPos;
    destinationPos.x = _Entity.getX();
    destinationPos.y = _Entity.getY();
    destinationPos.w = 247;
    destinationPos.h = 247;

    SDL_RenderCopy(gameRenderer, _Entity.getTexture(), &startPos, &destinationPos);
}

void renderWindow::renderTexture (SDL_Texture* currentTexture) {
    SDL_RenderCopy(gameRenderer, currentTexture, NULL, NULL);
}


void renderWindow::displayTexture () {
    SDL_RenderPresent(gameRenderer);
}