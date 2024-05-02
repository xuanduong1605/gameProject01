#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <entity.h>

Entity::Entity () {

}

Entity::Entity (Vector2d _Pos, SDL_Texture* _Texture) {
    pos = _Pos;
    texture = _Texture;
    frame = {0, 0, 32, 32};
    SDL_QueryTexture(_Texture, NULL, NULL, &frame.w, &frame.h);
}

Vector2d& Entity::getPos() {
    return pos;
}

void Entity::setPos (float _X, float _Y) {
    pos.x = _X;
    pos.y = _Y;
}

float Entity::getAngle () {
    return angle;
}

void Entity::setAngle (float _Angle) {
    angle = _Angle;
}

Vector2d Entity::getScale () {
    return scale;
}

void Entity::setScale (Vector2d _Scale) {
    scale = _Scale;
}

SDL_Texture* Entity::getTexture () {
    return texture;
}

SDL_Rect Entity::getFrame () {
    return frame;
}
