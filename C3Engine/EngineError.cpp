#include "EngineError.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>

namespace C3Engine
{
	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		system("pause");
		SDL_Quit();
		exit(-1);
	}
}