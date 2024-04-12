#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <entity.h>

Entity::Entity () {

}

Entity::Entity (float _x, float _y, SDL_Texture* _Texture) {
    xPos = _x;
    yPos = _y;
    currentTexture = _Texture;
    currentFrame = {0, 0, 0, 0};
}

float Entity::getX () {
    return xPos;
}

float Entity::getY () {
    return yPos;
}

SDL_Texture* Entity::getTexture () {
    return currentTexture;
}

SDL_Rect Entity::getFrame () {
    return currentFrame;
}
