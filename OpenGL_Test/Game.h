#pragma once
#include <C3Engine/GLSLProgram.h>
#include <C3Engine/GLTexture.h>
#include <C3Engine/Sprite.h>
#include <C3Engine/Window.h>
#include <C3Engine/Camera2D.h>
#include <C3Engine/SpriteBatch.h>

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

	C3Engine::GLSLProgram _colorProgram;
	C3Engine::Camera2D _camera;
	C3Engine::SpriteBatch _spriteBatch;

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

