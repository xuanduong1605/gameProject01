#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector2d.h>
#include <entity.h>

class Sea : public Entity {
    private:

    public: 

        Sea(Vector2d _Pos, SDL_Texture* _Texture);
};