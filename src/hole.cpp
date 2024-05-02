#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <entity.h>
#include <hole.h>

golfHole::golfHole (Vector2d _Pos, SDL_Texture* _Texture) : Entity(_Pos, _Texture) {

}