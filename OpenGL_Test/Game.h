#pragma once
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

	void init();
	void handleEvents();
	void gameLoop();
};

