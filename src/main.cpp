#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <vector2d.h>
#include <entity.h>
#include <renderWindow.h>
#include <ball.h>
#include <hole.h>
#include <box.h>

const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;

const double pi = 3.1415926;

renderWindow gameWindow("Golf", GAME_WIDTH, GAME_HEIGHT);

std::string basePath = std::string(SDL_GetBasePath());

SDL_Texture* backgroundTexture = gameWindow.loadTexture((basePath + "data/images/greenbg.png").c_str());
SDL_Texture* ballTexture = gameWindow.loadTexture((basePath + "data/images/ball.png").c_str());
SDL_Texture* arrowTexture = gameWindow.loadTexture((basePath + "data/images/arrow.png").c_str());
SDL_Texture* holeTexture = gameWindow.loadTexture((basePath + "data/images/hole.png").c_str());
SDL_Texture* boxTexture = gameWindow.loadTexture((basePath + "data/images/box.png").c_str());
SDL_Texture* logoTexture = gameWindow.loadTexture((basePath + "data/images/gamelogo.png").c_str());
SDL_Texture* endgameBackgroundTexture = gameWindow.loadTexture((basePath + "data/images/end_background.png").c_str());

Mix_Chunk* swingSound = nullptr;
Mix_Chunk* holeSound = nullptr;
Mix_Chunk* collideSound = nullptr;
Mix_Chunk* backgroundMusic = nullptr;

TTF_Font* font32 = nullptr;
TTF_Font* font48 = nullptr;
TTF_Font* font64 = nullptr;

SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};
SDL_Color darkGreen = {10, 85, 10};

golfBall ball(Vector2d(0, 0), ballTexture, arrowTexture);
golfHole hole(Vector2d(0, 0), holeTexture);

SDL_Event event;

bool gameRunning = 1;
bool mouseDown = 0;
bool mousePressed = 0;

int currentScreen = 0; // 0 = start, 1 = in-game, 2 = end game.
int level = 1;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;

double deltaTime = 0;

std::vector <Box> boxes;

void mainMenu() {
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double) SDL_GetPerformanceFrequency());

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameRunning = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				currentScreen = 1;
			}
			break;
		}
	}
	gameWindow.clearRenderer();
	gameWindow.renderTexture(0, 0, backgroundTexture);
	gameWindow.renderTexture(640 - 267, 360 - 205 - 40 + 20 * SDL_sin(SDL_GetTicks()* (pi / 1500)), logoTexture);
	gameWindow.renderTextCenter(300, "CLICK TO START", font32, darkGreen);
	gameWindow.displayTexture();
}

void loadLevel() {
	if (level > 4) {
		currentScreen = 2;
		return;
	}

	ball.setVelocity(0, 0);
	ball.setScale(Vector2d(1, 1));
	ball.setWin(0);
	boxes.clear();

	switch (level) {
		case 1:
			ball.setPos(200, 360 - 8);
			hole.setPos(1100, 360 - 8);
		break;

		case 2:
			ball.setPos(200, 360 - 8);
			hole.setPos(1100, 360 - 8);

			boxes.push_back({Vector2d(500, 360 - 67), boxTexture});
		break;

		case 3:
			ball.setPos(200, 360 - 8);
			hole.setPos(1100, 360 - 8);


		break;

		case 4:
			ball.setPos(200, 360 - 8);
			hole.setPos(1100, 360 - 8);


		break;
	}
}

void Update () {	
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double) SDL_GetPerformanceFrequency());
	
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
	ball.ballUpdate(deltaTime, mouseDown, mousePressed, hole, boxes, holeSound, swingSound, collideSound);
	if (ball.getScale().x < -1) {
		level++;
		loadLevel();
	}
}

const char* getLevelText () {
	std::string s = std::to_string(level);
	s = "LEVEL: " + s;
	return s.c_str();
}

void printLevel () {
	gameWindow.renderTextCenter(-328, getLevelText(), font32, black);
    gameWindow.renderTextCenter(-330, getLevelText(), font32, white);
}

const char* getStrokesText () {
	int strokes = ball.getStrokes();
	std::string s = std::to_string(strokes);
	s = "STROKES: " + s;
	return s.c_str();
}

void printStrokes () {
    gameWindow.renderTextCenter(332, getStrokesText(), font32, white);
	gameWindow.renderTextCenter(330, getStrokesText(), font32, black);
}

void endMenu () {
	gameWindow.renderTexture(0, 0, endgameBackgroundTexture);
	gameWindow.renderTextCenter(3 - 32, "GAME OVER!", font48, black);
	gameWindow.renderTextCenter(-32, "GAME OVER!", font48, white);
	gameWindow.renderTextCenter(25, getStrokesText(), font32, black);
	gameWindow.renderTextCenter(22, getStrokesText(), font32, white);
}

void renderGraphics() {
	gameWindow.clearRenderer();

	gameWindow.renderTexture(0, 0, backgroundTexture);

	if (currentScreen == 1) {
		gameWindow.renderEntity(hole);
		gameWindow.renderEntity(ball.getArrow());
		gameWindow.renderEntity(ball);

		for (Box& box : boxes) { 
			gameWindow.renderEntity(box);
		}

		printStrokes();
		printLevel();
	}
	else {
		endMenu();
	}

	gameWindow.displayTexture();
}

int main (int argc, char **argv) {

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
	Mix_Init(MIX_INIT_WAVPACK);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	swingSound = Mix_LoadWAV((basePath + "data/audio/hit.wav").c_str());
	holeSound = Mix_LoadWAV((basePath + "data/audio/hole.wav").c_str());
	collideSound = Mix_LoadWAV((basePath + "data/audio/collide.wav").c_str());
	backgroundMusic = Mix_LoadWAV((basePath + "data/audio/backgroundmusic.wav").c_str());

	font32 = TTF_OpenFont((basePath + "data/fonts/font.ttf").c_str(), 32);
	font48 = TTF_OpenFont((basePath + "data/fonts/font.ttf").c_str(), 48);
	font64 = TTF_OpenFont((basePath + "data/fonts/font.ttf").c_str(), 64);

	Mix_PlayChannel(-1, backgroundMusic, 0);

	bool menuMusic = 1;

	loadLevel();

    while (gameRunning) {
		if (!currentScreen) {
			mainMenu();
		}
		else {
			if (menuMusic) {
				Mix_Pause(-1);
				menuMusic = 0;
			}
			Update();
			renderGraphics();
		}
    }

    gameWindow.cleanUp();
	Mix_Quit();
    SDL_Quit();
	IMG_Quit();
	TTF_Quit();

    return 0;
}