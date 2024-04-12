#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
    private:

        float xPos, yPos;
        SDL_Rect currentFrame;
        SDL_Texture* currentTexture;

    public:

        Entity();

        Entity(float _x, float _y, SDL_Texture* _Texture);

        float getX();

        float getY();

        SDL_Texture* getTexture();

        SDL_Rect getFrame();

};