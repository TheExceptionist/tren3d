#include <stdio.h>
#include "SDL2/SDL.h"


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Could not initialize SDL2! Error: %s\n", SDL_GetError());
	}

	return 0;
}