#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector2d.h>
#include <entity.h>
#include <ball.h>

const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;
const float BALL_FRICTION = 0.0001;

golfBall::golfBall (Vector2d _Pos, SDL_Texture* _Texture, SDL_Texture* _Arrow) : Entity(_Pos, _Texture) {
    dirArrow = Entity(Vector2d(0, 0), _Arrow);
}

Vector2d& golfBall::getVelocity () {
    return velocity2D;
}

Vector2d& golfBall::getOrgMousePosition () {
    return orgMousePosition;
}

Entity golfBall::getArrow () {
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

void golfBall::ballUpdate(double deltaTime, bool mouseDown, bool mousePressed) {
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

        setVelocity(deltaX / -150, deltaY / -150);;
        setLaunchedVelocity(deltaX / -150, deltaY / -150);
        velocity1D = launchedVelocity1D = getHypotenuse(getVelocity());
        if (velocity1D > 1) {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
        dirX = velocity2D.x > 0 ? 1 : -1;
        dirY = velocity2D.y > 0 ? 1 : -1;
    }
    else {
        moving = 1;
        setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
        if (getVelocity().x > BALL_FRICTION || getVelocity().x < -BALL_FRICTION || getVelocity().y > BALL_FRICTION || getVelocity().y < -BALL_FRICTION) {
            if (velocity1D > 0) {
                velocity1D -= BALL_FRICTION * deltaTime;
            }
            else {
                velocity1D = 0;
            }
            velocity2D.x = (velocity1D / launchedVelocity1D) * abs(launchedVelocity2D.x) * dirX;
            velocity2D.y = (velocity1D / launchedVelocity1D) * abs(launchedVelocity2D.y) * dirY;
        }
        else {
            setVelocity(0, 0);
            int mouseX = 0,
	            mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            setOrgMousePosition(mouseX, mouseY);
            moving = 0;
        }

        if (getPos().x + getFrame().w > GAME_WIDTH) {
            std::cout << "RIGHT" << '\n';
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        else if (getPos().x < 0) {
            std::cout << "LEFT" << '\n';
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        else if (getPos().y + getFrame().h > GAME_HEIGHT) {
            std::cout << "BOTTOM" << '\n';
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1;
        }
        else if (getPos().y < 0) {
            std::cout << "TOP" << '\n';
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1;
        }
    }
};
