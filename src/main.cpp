#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector2d.h>
#include <entity.h>
#include <renderWindow.h>
#include <ball.h>
#include <hole.h>

const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;

renderWindow gameWindow("Gaycorn", GAME_WIDTH, GAME_HEIGHT);

std::string basePath = std::string(SDL_GetBasePath());

SDL_Texture* backgroundTexture = gameWindow.loadTexture((basePath + "data/images/greenbg.png").c_str());
SDL_Texture* ballTexture = gameWindow.loadTexture((basePath + "data/images/ball.png").c_str());
SDL_Texture* arrowTexture = gameWindow.loadTexture((basePath + "data/images/arrow.png").c_str());
SDL_Texture* holeTexture = gameWindow.loadTexture((basePath + "data/images/hole.png").c_str());

golfBall ball(Vector2d(0, 0), ballTexture, arrowTexture);
golfHole hole(Vector2d(0, 0), holeTexture);

SDL_Event event;

bool gameRunning = 1;
bool mouseDown = 0;
bool mousePressed = 0;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void Update () {	
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
	
	mousePressed = 0;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameRunning = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseDown = 1;
				mousePressed = 1;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseDown = 0;
			}
			break;
		}    
	}
	ball.ballUpdate(deltaTime, mouseDown, mousePressed, hole);
}

void renderGraphics() {
	gameWindow.clearRenderer();

	gameWindow.renderTexture(0, 0, backgroundTexture);
	gameWindow.renderEntity(hole);
	gameWindow.renderEntity(ball.getArrow());
	gameWindow.renderEntity(ball);

	gameWindow.displayTexture();
}

int main (int argc, char **argv) {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

	hole.setPos(512, 512);
	ball.setPos(256, 512);
	 
    while (gameRunning) {
        Update();
        renderGraphics();
    }

    gameWindow.cleanUp();
    SDL_Quit();

    return 0;
}