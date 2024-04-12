#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <renderWindow.h>

renderWindow::renderWindow () {

}

void renderWindow::createWindow (const char* windowTitle, int windowWidth, int windowHeight)  {
  gameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

  if (gameWindow == NULL) {
		std::cout << "Window failed to init. Error: " << SDL_GetError() << '\n';
  }

	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
}

void renderWindow::cleanUp () {
  SDL_DestroyWindow(gameWindow);
}

void renderWindow::clearRenderer () {
  SDL_SetRenderDrawColor(gameRenderer, 90, 90, 90, 255);
	SDL_RenderClear(gameRenderer);
}

SDL_Texture* renderWindow::loadTexture (const char* filePath) {
  SDL_Texture* currentTexture = NULL;
  currentTexture = IMG_LoadTexture(gameRenderer, filePath);

  if (currentTexture == NULL) {
    std::cout << "Failed to load texture. Error: " << SDL_GetError() << '\n';
  }

  return currentTexture;
}

void renderWindow::renderTexture (SDL_Texture* currentTexture) {
  SDL_RenderCopy(gameRenderer, currentTexture, NULL, NULL);
}

void renderWindow::displayTexture () {
  SDL_RenderPresent(gameRenderer);
}