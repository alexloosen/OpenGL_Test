#include "Errors.h"
#include "SDL.h"
#include <iostream>
#include <cstdlib>

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	system("pause");
	SDL_Quit();
	exit(-1);
}