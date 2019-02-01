#include "Window.h"
#include "EngineError.h"

namespace C3Engine
{
	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int flags)
	{
		Uint32 currentFlags = SDL_WINDOW_OPENGL;
		if (flags & INVISIBLE)
		{
			currentFlags |= SDL_WINDOW_HIDDEN;
		}
		if (flags & FULLSCREEN)
		{
			currentFlags |= SDL_WINDOW_FULLSCREEN;
		}
		if (flags & BORDERLESS)
		{
			currentFlags |= SDL_WINDOW_BORDERLESS;
		}

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, currentFlags);

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

		std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));
		glClearColor(0.0f, 1.0f, 0.0f, 1.0);

		SDL_GL_SetSwapInterval(0);
		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_window);
	}
}