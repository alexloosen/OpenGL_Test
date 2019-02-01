#pragma once
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"

#include <SDL.h>
#include <glew.h>
#include <vector>

enum class GameState{PLAY,EXIT};

class Game
{
	public:
	Game();
	~Game();

	void run();

	private:
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	std::vector<Sprite*> _sprites;

	GLSLProgram _colorProgram;
	float _time;

	void init();
	void initShaders();
	void handleEvents();
	void gameLoop();
	void render();
};

