#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector2d.h>

class Entity {
    private:

        Vector2d pos;
        float angle;
        Vector2d scale = Vector2d(1, 1);

        SDL_Rect frame;
        SDL_Texture* texture;

    public:

        Entity();

        Entity(Vector2d _Pos, SDL_Texture* _Texture);

        Vector2d getPos();

        void setPos(Vector2d _Pos);

        float getAngle();

        void setAngle(float _Angle);

        Vector2d getScale();

        void setScale(Vector2d _Scale);

        SDL_Texture* getTexture();

        SDL_Rect getFrame();
};