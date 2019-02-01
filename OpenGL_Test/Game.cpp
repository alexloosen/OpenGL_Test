#include "Game.h"
#include <C3Engine/C3Engine.h>
#include <C3Engine/EngineError.h>
#include <iostream>
#include <string>

Game::Game() : _screenHeight(768), _screenWidth(1024), _time(0), _gameState(GameState::PLAY), _maxFPS(60.0f)
{
}


Game::~Game()
{
}

void Game::run()
{
	init();
	_sprites.push_back(new C3Engine::Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "..\\textures\\PNG\\CharacterRight_Standing.png");
	_sprites.push_back(new C3Engine::Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "..\\textures\\PNG\\CharacterRight_Standing.png");
	gameLoop();
}

void Game::init()
{
	C3Engine::init();
	int test = _window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);
	initShaders();
}

void Game::initShaders()
{
	_colorProgram.compileShaders("..\\shaders\\colorShading.vert", "..\\shaders\\colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void Game::handleEvents()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
		_gameState = GameState::EXIT;
		break;
		case SDL_MOUSEMOTION:
		//std::cout << "X: " << e.motion.x << " Y: " << e.motion.y << std::endl;
		break;
		}
	}
}

void Game::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();
		handleEvents();
		_time += 0.01;
		render();
		calculateFPS();
		static int frameCount = 0;
		frameCount++;
		if (frameCount == 10)
		{
			std::cout << "FPS: " << (int)_fps << std::endl;
			frameCount = 0;
		}
		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
	}
}

void Game::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	_window.swapBuffer();
}

void Game::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	float currentTicks;
	int count;

	static float prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();
	_frameTime = currentTicks - prevTicks;

	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 0;
	}
}
