#include "Game.h"
#include "Errors.h"
#include <iostream>
#include <string>

Game::Game() : _screenHeight(768), _screenWidth(1024), _time(0), _window(nullptr), _gameState(GameState::PLAY), _maxFPS(200.0f)
{
}


Game::~Game()
{
}

void Game::run()
{
	init();
	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "..\\textures\\PNG\\CharacterRight_Standing.png");
	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "..\\textures\\PNG\\CharacterRight_Standing.png");
	gameLoop();
}

void Game::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (!_window)
	{
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (!glContext)
	{
		fatalError("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0);
	//glEnable(GL_BLEND);
	//glBlendFunct(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	SDL_GL_SwapWindow(_window);
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
