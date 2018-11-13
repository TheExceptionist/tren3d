/*
========================================================
File: Main.cpp
Author: Kenneth Stepney
Purpose: Main entry point for the program


========================================================
*/


#include <stdio.h>
#include "display.h"
#include "render.h"

static bool g_running = true;

int main(int argc, char* argv[])
{
	Display display("TREN3D.exe", 800, 640);

	if (!display.init())
	{
		printf("Could not initialize display!\n");
	}

	Render render(display);

	if (!render.init())
	{
		printf("Could not initialize render!\n");
	}

	InputManager input = InputManager();

	if (!input.init())
	{
		printf("Could not initialize input!\n");
	}

	Entity player("Lambert", 5, 3);
	render.setPlayer(&player);
	//input.setPlayer(&player);

	while (display.isRunning())
	{
		display.clearColor(&BLUE);
		//render.update();

		display.update();
	}

	return 0;
}