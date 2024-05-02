#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector2d.h>
#include <entity.h>

class golfHole : public Entity {
    private:

    public: 

        golfHole(Vector2d _Pos, SDL_Texture* _Texture);
};