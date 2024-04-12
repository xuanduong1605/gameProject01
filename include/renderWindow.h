#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class renderWindow {
    private:

        SDL_Window* gameWindow;
        SDL_Renderer* gameRenderer;

    public:

        renderWindow();

        void createWindow(const char* windowTitle, int windowWidth, int windowHeight);

        void cleanUp();

        void clearRenderer();

        SDL_Texture* loadTexture (const char* filePath);

        void renderTexture(SDL_Texture* currentTexture);

        void displayTexture();
    
};