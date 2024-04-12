#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <entity.h>

class renderWindow {
    private:

        SDL_Window* gameWindow;
        SDL_Renderer* gameRenderer;

    public:

        renderWindow();

        void createWindow(const char* _Title, int _Width, int _Height);

        void cleanUp();

        void clearRenderer();

        SDL_Texture* loadTexture (const char* _filePath);

        void renderTexture(Entity _Entity);

        void renderTexture(SDL_Texture* _Texture);

        void displayTexture();
    
};