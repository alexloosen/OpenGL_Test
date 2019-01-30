#include "Errors.h"
#include "SDL.h"
#include <iostream>

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	system("pause");
	SDL_Quit();
}