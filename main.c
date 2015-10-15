#include <stdbool.h>

#include <SDL_image.h>


int main(int argc, char *argv[])
{
	SDL_Surface *s = NULL;
	SDL_Surface *screen = NULL;

	// Check args
	if (argc != 2)
	{
		printf("Usage: sdl_image_test <filename>\n");
		goto bail;
	}

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init error: %s\n", SDL_GetError());
		goto bail;
	}

	// Load image from file
	s = IMG_Load(argv[1]);
	if (s == NULL)
	{
		printf("Failed to load image from file %s\n", argv[1]);
		goto bail;
	}

	// Create display window based on image size
	SDL_WM_SetCaption(argv[1], NULL);
	screen = SDL_SetVideoMode(s->w, s->h, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL)
	{
		printf("Failed to set video mode: %s\n", SDL_GetError());
		goto bail;
	}

	// Convert to the correct format
	SDL_Surface *s2 = SDL_DisplayFormat(s);
	if (s2 == NULL)
	{
		printf("Failed to convert surface: %s\n", SDL_GetError());
		goto bail;
	}
	s = s2;

	// Blit the image to screen
	if (SDL_BlitSurface(s, NULL, screen, NULL) != 0)
	{
		printf("Failed to blit surface: %s\n", SDL_GetError());
		goto bail;
	}

	// Display
	if (SDL_Flip(screen) != 0)
	{
		printf("Failed to flip surface: %s\n", SDL_GetError());
		goto bail;
	}

	// Wait for keypress to exit
	bool quit = false;
	while (!quit)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_Delay(100);
	}


bail:
	SDL_FreeSurface(screen);
	SDL_FreeSurface(s);
	SDL_Quit();
	return 0;
}
