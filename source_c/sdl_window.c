#include "../headers/main.h"

/**
 * init_instance - intialize all instances
 * @in: instance
 *
 * Return: 0 on success 1 otherwise
 **/

int init_instance(SDL_Instance *in)
{
	/* if window is not initialized */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* create window with given height and width */
	in->win = SDL_CreateWindow("The Maze Portfolio Project", 0, 0, SCREEN_WIDTH,
	SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	/* if not window */
	if (in->win == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* renderer */
	in->ren = SDL_CreateRenderer(in->win, -1, SDL_RENDERER_ACCELERATED
	| SDL_RENDERER_PRESENTVSYNC);
	/* if not renderer */
	if (in->ren == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* if image not initialized */
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "Failed to initialize SDL_image.\n");
		return (1);
	}
	return (0);
}

/**
 * FixAng - reset angle if above the range
 * @a: the given angle
 *
 * Return: the converted angle
 **/
float FixAng(float a)
{
	/* if the angle is above 360 degeree */
	if (a > 2 * PI)
		a -= 2 * PI;
	/* if the angle is negative */
	if (a < 0)
		a += 2 * PI;
	return (a);
}

