#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <renderWindow.h>
#include <entity.h>

renderWindow::renderWindow () {

}

renderWindow::renderWindow (const char *_Title, int _Width, int _Height) {
    gameWindow = SDL_CreateWindow(_Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _Width, _Height, SDL_WINDOW_SHOWN);

    if (gameWindow == NULL) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << '\n';
    }

    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

void renderWindow::renderEntity (Entity& _Entity) {
	SDL_Rect src = _Entity.getFrame(); 

	SDL_Rect dst;
	dst.x = _Entity.getPos().x + (_Entity.getFrame().w - _Entity.getFrame().w * _Entity.getScale().x) / 2;
	dst.y = _Entity.getPos().y + (_Entity.getFrame().h - _Entity.getFrame().h * _Entity.getScale().y) / 2;
	dst.w = _Entity.getFrame().w * _Entity.getScale().x;
	dst.h = _Entity.getFrame().h * _Entity.getScale().y;

	SDL_RenderCopyEx(gameRenderer, _Entity.getTexture(), &src, &dst, _Entity.getAngle(), 0, SDL_FLIP_NONE);
}

void renderWindow::renderTexture (int _X, int _Y, SDL_Texture* _Texture) {
	SDL_Rect src = {0, 0, 0, 0}; 

	SDL_QueryTexture(_Texture, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst = {_X, _Y, src.w, src.h};

	SDL_RenderCopy(gameRenderer, _Texture, &src, &dst);
}

void renderWindow::displayTexture () {
    SDL_RenderPresent(gameRenderer);
}

void renderWindow::renderText (float _X, float _Y, const char* _Text, TTF_Font* _Font, SDL_Color _TextColor) {
    SDL_Surface* surface = TTF_RenderText_Blended(_Font, _Text, _TextColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(gameRenderer, surface);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surface->w;
    src.h = surface->h; 

    SDL_Rect dst;
    dst.x = _X;
    dst.y = _Y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(gameRenderer, message, &src, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}
