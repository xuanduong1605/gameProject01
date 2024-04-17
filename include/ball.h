#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector2d.h>
#include <entity.h>


class golfBall : public Entity {
    private:

        Vector2d velocity2D;
        Vector2d target;
        Vector2d launchedVelocity2D;
        Vector2d orgMousePosition;

        float velocity1D;
        float launchedVelocity1D;

        bool playSwingFx = 1;
        bool win = 0;
        bool moving = 0;

        int index;
        int strokes = 0;
        int dirX = 1;
        int dirY = 1;
        
        Entity dirArrow;

    public:

        golfBall(Vector2d _Pos, SDL_Texture* _Texture, SDL_Texture* _Arrow);

        Vector2d& getVelocity();

        Vector2d& getOrgMousePosition();

        Entity getArrow();

        int getStrokes();

        bool getWin();

        void setWin(bool _Win);

        void setOrgMousePosition(float _X, float _Y);

        void setVelocity(float _X, float _Y);

        void setLaunchedVelocity(float _X, float _Y);

        void ballUpdate(double deltaTime, bool mouseDown, bool mousePressed);

};