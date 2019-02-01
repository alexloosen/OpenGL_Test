#pragma once
#include <SDL.h>
#include <glew.h>

#include <string>

namespace C3Engine
{
	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
		public:
		Window();
		~Window();
		int createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int flags);

		int getScreenWidth()
		{
			return _screenWidth;
		}
		int getScreenHeigth()
		{
			return _screenHeight;
		}

		void swapBuffer();
		private:
		int _screenWidth;
		int _screenHeight;
		SDL_Window * _window;
	};
}