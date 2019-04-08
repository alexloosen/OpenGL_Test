#include "Game.h"
#include <C3Engine/C3Engine.h>
#include <C3Engine/EngineError.h>
#include <C3Engine/ResourceManager.h>
#include <iostream>
#include <string>
#include <math.h>

Game::Game() : _screenHeight(768), _screenWidth(1366), _time(0), _gameState(GameState::PLAY), _maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}


Game::~Game()
{
}

void Game::run()
{
	init();
	//_sprites.push_back(new C3Engine::Sprite());
	//_sprites.back()->init(0.0f, 0.0f, _screenWidth / 2, _screenWidth / 2, "..\\textures\\PNG\\CharacterRight_Standing.png");
	//_sprites.push_back(new C3Engine::Sprite());
	//_sprites.back()->init(_screenWidth / 2, 0.0f, _screenWidth / 2, _screenWidth / 2, "..\\textures\\PNG\\CharacterRight_Standing.png");
	gameLoop();
}

void Game::init()
{
	C3Engine::init();
	int test = _window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
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

	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;

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
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
				break;
			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
				break;
			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
				break;
			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
				break;
			case SDLK_q:
				_camera.setScale(_camera.getScale() + SCALE_SPEED);
				break;
			case SDLK_e:
				_camera.setScale(_camera.getScale() - SCALE_SPEED);
				break;

			}
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

		_camera.update();

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

	//camera
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();
	glm::vec4 pos(0.0f, 0.0f, 50, 50);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	C3Engine::GLTexture texture;
	C3Engine::GLTexture water = C3Engine::ResourceManager::getTexture("..\\textures\\PNG\\water.png");
	if (sin(4*_time) > 0.5)
	{
		texture = C3Engine::ResourceManager::getTexture("..\\textures\\PNG\\CharacterRight_Standing_.png");
	}
	else
	{
		texture = C3Engine::ResourceManager::getTexture("..\\textures\\PNG\\CharacterLeft_Standing.png");
	}
	C3Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	_spriteBatch.draw(pos, uv, water.id, 0.0f, color);
	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	_spriteBatch.draw(pos + glm::vec4(0, 50, 0, 0), uv, texture.id, 0.0f, color);
	_spriteBatch.draw(pos + glm::vec4(50, 50, 0, 0), uv, texture.id, 0.0f, color);
	_spriteBatch.draw(pos + glm::vec4(100, 50, 0, 0), uv, texture.id, 0.0f, color);
	_spriteBatch.draw(pos + glm::vec4(150, 50, 0, 0), uv, texture.id, 0.0f, color);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

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
