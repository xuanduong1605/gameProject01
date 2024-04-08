#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <renderWindow.h>

renderWindow::renderWindow() {
    
}

void renderWindow::RenderWindow(const char* windowTitle, int windowWidth, int windowHeight)  {
    gameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if (gameWindow == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << '\n';

	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
}