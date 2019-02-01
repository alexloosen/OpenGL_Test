#include "C3Engine.h"
#include <SDL.h>
#include <glew.h>

namespace C3Engine
{
	int init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}
}