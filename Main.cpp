#include <SDL.h>
#include <iostream>
#include "ImageConverter.h"
using namespace std;
#ifdef main
#undef main
#endif

int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	atexit(SDL_Quit);
	ImageConverter converter("obrazek2.bmp");

	bool done = false;
	while (!done)
	{
		// message processing loop
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// check for messages
			switch (event.type)
			{
				// exit if the window is closed
			case SDL_QUIT:
				done = true;
				break;

				// check for keypresses
			case SDL_KEYDOWN:
			{
				// exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = true;
				if (event.key.keysym.sym == SDLK_1) {
					//standard("standard.karol", false);
					continue;
				}
				/*
				if (event.key.keysym.sym == SDLK_2) {
					bmpToGrey("grey.karol", false);
				}
				if (event.key.keysym.sym == SDLK_3)
					standard("standard.karol", true);
				if (event.key.keysym.sym == SDLK_4)
					bmpToGrey("grey.karol", true);
				if (event.key.keysym.sym == SDLK_5)
					loadImage("standard.karol", false);*/
				if (event.key.keysym.sym == SDLK_6) {
					SDL_Quit();
					done = true;
				}
				/*if (event.key.keysym.sym == SDLK_7)
					dithering();
				if (event.key.keysym.sym == SDLK_8)
					loadImage("grey.karol", true);*/
				if (event.key.keysym.sym == SDLK_a)
					converter.loadBMP("Uncle Dercius.bmp");
				if (event.key.keysym.sym == SDLK_s)
					converter.loadBMP("obrazek2.bmp");
				if (event.key.keysym.sym == SDLK_d)
					converter.loadBMP("obrazek3.bmp");
				if (event.key.keysym.sym == SDLK_b)
					converter.clearScreen();
				break;
			}
			} // end switch
		} // end of message processing

	} // end main loop


	//cin.get();
	return 0;
}