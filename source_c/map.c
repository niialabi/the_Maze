#include "../headers/main.h"

int map[map_y][map_x] = {
	{1, 1, 1, 1, 1, 3, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 4, 1, 0, 0, 0, 1},
	{2, 0, 0, 0, 0, 0, 0, 3},
	{2, 0, 0, 0, 1, 0, 0, 1},
	{2, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 2, 1, 1, 1, 1},
	};

int map_floor[map_y][map_x] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 2, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 2, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	};


/**
 * getmap_value - find map value at given coordinate
 * @x: x-axis
 * @y: y-axis
 * @mp: map type
 *
 * Return: the value at x,y
 **/
int getmap_value(int x, int y, int mp)
{
	if (mp == 1)
		return (map_floor[y][x]);
	else
		return (map[y][x]);
}

/**
 * setmap_value - set value of map at given coordinate
 * @x: x-axis
 * @y: y-axis
 * @val: the value to set
 *
 **/
void setmap_value(int x, int y, int val)
{
	/* set the map value to arg val */
	map[y][x] = val;
}

/**
 * make_map - make map from the given array
 * @argv: array of given argument
 *
 **/
void make_map(char **argv)
{
	int i, j;
	int **file_map;

	/* get the map value from file */
	file_map = get_altitude(argv);
	for (i = 0; i < map_x; i++)
	{
		for (j = 0; j < map_y; j++)
			map[i][j] = file_map[i][j];
	}
	free_numbers(file_map);
}

