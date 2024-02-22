#include "../headers/main.h"


/**
 * main - Entry point for execution
 * @argc: the number of argument
 * @argv: vector for the given argument
 *
 * Return: always success
 **/
int main(int argc, char **argv)
{
	/* instance variable */
	SDL_Instance instance;
	/* create & initialize the window */
	if (init_instance(&instance) != 0)
		return (1);
	/* Game initialization */
	init_game();
	if (argc > 1)
		make_map(argv);
	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.ren, 76, 76, 76, 0);
		SDL_RenderClear(instance.ren);

		/** handle user input */
		if (poll_events(instance) == 1)
			break;
		/* draw the wall, ceiling, map & sprit */
		display(instance);
		SDL_RenderPresent(instance.ren);
	}
	/* Destroy the renderer and the window, then quit.*/
	SDL_DestroyRenderer(instance.ren);
	SDL_DestroyWindow(instance.win);
	SDL_Quit();
	return (0);
}



