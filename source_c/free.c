#include "../headers/main.h"

/**
 * free_grid - free alloc mem of grid
 * @grid: the given grid
 *
 **/
void free_grid(SDL_Point ***grid)
{
	/* variables for x & y coord. */
	int i, j;

	/* free each row */
	for (j = 0; j < map_x; j++)
		free(grid[0][j]);
	free(grid[0]);
	/* free each column */
	for (i = 0; i < map_y; i++)
		free(grid[1][i]);
	free(grid[1]);
	free(grid);
}

/**
 * free_tokens - free the mem for tokens
 * @tokens: the given tokens
 *
 **/
void free_tokens(char **tokens)
{
	char **tmp = tokens;

	if (tokens)
	{
		while (*tokens)
			free(*tokens++);
		free(tmp);
	}
}
/**
 * free_cols - free alloc mem of columns
 * @cols: the given columns
 *
 **/
void free_cols(char ***cols)
{
	int i, j;

	for (i = 0; i < map_x; i++)
	{
		for (j = 0; j < map_y; j++)
			free(cols[i][j]);
		free(cols[i]);
	}
	free(cols);
}

/**
 * free_numbers - free number assigned memory
 * @numbers: the given numbers
 *
 **/
void free_numbers(int **numbers)
{
	int i;

	for (i = 0; i < map_x; i++)
		free(numbers[i]);
	free(numbers);
}


