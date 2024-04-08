#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class renderWindow {
    private:
        SDL_Window* gameWindow;
        SDL_Renderer* gameRenderer;
    public:
        renderWindow();

        void RenderWindow(const char* windowTitle, int windowWidth, int windowHeight);
    
};