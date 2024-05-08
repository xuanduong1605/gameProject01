#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <ball.h>
#include <entity.h>

class renderWindow {
    private:

        SDL_Window* gameWindow;
        SDL_Renderer* gameRenderer;

    public:

        renderWindow();

        renderWindow(const char* _Title, int _Width, int _Height);

        void cleanUp();

        void clearRenderer();

        SDL_Texture* loadTexture (const char* _filePath);

        void renderEntity(Entity& _Entity);

        void renderTexture(int _X, int _Y, SDL_Texture* _Texture);

        void renderText(float _X, float _Y, const char* _Text, TTF_Font* _Font, SDL_Color _TextColor);

        void renderTextCenter (float _Y, const char* _Text, TTF_Font* _Font, SDL_Color _TextColor);

        void displayTexture();
};