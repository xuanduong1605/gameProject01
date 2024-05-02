#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector2d.h>
#include <entity.h>
#include <ball.h>
#include <hole.h>

const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;
const int SPEED_RATIO = -125;

const float BALL_FRICTION = 0.0005;
const float BALL_DOWNSCALE = 0.002;
const float pi = 3.1415926;

golfBall::golfBall (Vector2d _Pos, SDL_Texture* _Texture, SDL_Texture* _Arrow) : Entity(_Pos, _Texture) {
    dirArrow = Entity(Vector2d(0, 0), _Arrow);
}

Vector2d& golfBall::getVelocity () {
    return velocity2D;
}

Vector2d& golfBall::getOrgMousePosition () {
    return orgMousePosition;
}

Entity& golfBall::getArrow () {
    return dirArrow;
}

int golfBall::getStrokes () {
    return strokes;
}

bool golfBall::getWin () {
    return win;
}

void golfBall::setWin (bool _Win) {
    win = _Win;
}

void golfBall::setOrgMousePosition (float _X, float _Y) {
    orgMousePosition.x = _X;
    orgMousePosition.y = _Y;
}

void golfBall::setVelocity (float _X, float _Y) {
    velocity2D.x = _X;
    velocity2D.y = _Y;
}

void golfBall::setLaunchedVelocity (float _X, float _Y) {
    launchedVelocity2D.x = _X;
    launchedVelocity2D.y = _Y;
}

float getHypotenuse (Vector2d &a) {
    return SDL_sqrt(a.x * a.x + a.y * a.y);
}

float getAbs (float &a) {
    if (a < 0) return -a;
    return a;
}

void golfBall::ballUpdate(double deltaTime, bool mouseDown, bool mousePressed, golfHole hole) {
    if (win) {
        if (getPos().x < target.x) {
            setPos(getPos().x += 0.1 * deltaTime, getPos().y);
        }
        else if (getPos().x > target.x) {
            setPos(getPos().x -= 0.1 * deltaTime, getPos().y);
        }
        if (getPos().y < target.y) {
            setPos(getPos().x, getPos().y += 0.1 * deltaTime);
        }
        else if (getPos().y > target.y) {
            setPos(getPos().x, getPos().y -= 0.1 * deltaTime);
        }
        setScale(Vector2d(getScale().x - BALL_DOWNSCALE * deltaTime, getScale().y - BALL_DOWNSCALE * deltaTime));
        return;
    }
    
    if (getPos().x + 4 > hole.getPos().x && getPos().x + 16 < hole.getPos().x + 20 && getPos().y + 4 > hole.getPos().y && getPos().y + 16 < hole.getPos().y + 20 && velocity1D < 0.5) {
        setWin(1);
        target.x = hole.getPos().x ;
        target.y = hole.getPos().y + 3;
    }

    if (mousePressed && !moving) {
        int mouseX = 0, 
            mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setOrgMousePosition(mouseX, mouseY);
    }

    if (mouseDown && !moving) {
        int mouseX = 0, 
            mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        float deltaX = mouseX - getOrgMousePosition().x,
              deltaY = mouseY - getOrgMousePosition().y;

        setVelocity(deltaX / SPEED_RATIO, deltaY / SPEED_RATIO);;
        setLaunchedVelocity(deltaX / SPEED_RATIO, deltaY / SPEED_RATIO);

        velocity1D = launchedVelocity1D = getHypotenuse(getVelocity());
        if (velocity1D > 1) {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }

        std::cout << getVelocity().x << ' ' << getVelocity().y << '\n';

        dirArrow.setPos(getPos().x, getPos().y + 8 - 32);
        dirArrow.setAngle(SDL_atan2(velocity2D.y, velocity2D.x) * (180 / pi) + 90);

        dirX = velocity2D.x > 0 ? 1 : -1;
        dirY = velocity2D.y > 0 ? 1 : -1;
    }
    else {
        moving = 1;
        dirArrow.setPos(-100, -100);

        std::cout << getVelocity().x << ' ' << getVelocity().y << '\n';
        setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
        if (getVelocity().x > BALL_FRICTION || getVelocity().x < -BALL_FRICTION || getVelocity().y > BALL_FRICTION || getVelocity().y < -BALL_FRICTION) {
            if (velocity1D > 0) {
                velocity1D -= BALL_FRICTION * deltaTime;
            }
            else {
                velocity1D = 0;
            }
            velocity2D.x = (velocity1D / launchedVelocity1D) * getAbs(launchedVelocity2D.x) * dirX;
            velocity2D.y = (velocity1D / launchedVelocity1D) * getAbs(launchedVelocity2D.y) * dirY;
        }
        else {
            setVelocity(0, 0);
            moving = 0;
        }

        if (getPos().x + getFrame().w > GAME_WIDTH) {
            setVelocity(-getAbs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        if (getPos().x < 0) {
            setVelocity(getAbs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        if (getPos().y + getFrame().h > GAME_HEIGHT) {
            setVelocity(getVelocity().x, -getAbs(getVelocity().y));
            dirY = -1;
        }
        if (getPos().y < 0) {
            setVelocity(getVelocity().x, getAbs(getVelocity().y));
            dirY = 1;
        }
    }
};
