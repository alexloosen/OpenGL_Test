#pragma once
#include <C3Engine/GLSLProgram.h>
#include <C3Engine/GLTexture.h>
#include <C3Engine/Sprite.h>
#include <C3Engine/Window.h>
#include <C3Engine/Camera2D.h>

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
	C3Engine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	std::vector<C3Engine::Sprite*> _sprites;

	C3Engine::GLSLProgram _colorProgram;
	C3Engine::Camera2D _camera;

	float _time;

	float _fps;
	float _frameTime;
	float _maxFPS;

	void init();
	void initShaders();
	void handleEvents();
	void gameLoop();
	void render();
	void calculateFPS();
};

