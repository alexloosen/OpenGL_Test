#pragma once
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"

#include <SDL.h>
#include <glew.h>

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
	Sprite _sprite;
	GLTexture _playerTexture;

	GLSLProgram _colorProgram;
	float _time;

	void init();
	void initShaders();
	void handleEvents();
	void gameLoop();
	void render();
};

