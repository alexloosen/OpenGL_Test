#include "Game.h"
#include "Errors.h"
#include <iostream>
#include <string>

Game::Game() : _screenHeight(768), _screenWidth(1024), _time(0), _window(nullptr), _gameState(GameState::PLAY)
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
	for (int i = 0; i < 1000; i++)
	{
		_sprites.push_back(new Sprite());
		_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "..\\textures\\PNG\\CharacterRight_Standing.png");
	}
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
		handleEvents();
		_time += 0.01;
		render();
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
