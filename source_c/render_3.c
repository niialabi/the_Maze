#include "../headers/main.h"

/**
 * sort_sprite - sort the sprite
 * @sprite: the given sprite
 * @spr_dis: the distance of each sprite
 * @n: the  number of sprite
 *
 **/
void sort_sprite(int *sprite, double *spr_dis, int n)
{
	/* temporary variable for bubble sort */
	int i, j, t;
	double tmp;

	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			/* if the previous distance is less than the next */
			if (spr_dis[i] < spr_dis[j])
			{
				tmp = spr_dis[i];
				t = spr_dis[i];
				spr_dis[i] = spr_dis[j];
				sprite[i] = sprite[j];
				spr_dis[j] = tmp;
				sprite[j] = t;
			}
		}
	}
}

/**
 * display - function to display the game
 * @instance: the given sdl2 instance
 *
 **/
void display(SDL_Instance instance)
{
	ray_cast(instance);
	add_enemy(instance);
	render_map(instance);
	render_player(instance);
	add_weapon(instance);
	draw_sprite_map(instance);
}

/**
 * init_game - initialize maze
 *
 **/
void init_game(void)
{
	/* player initialization */
	player.x = 90;
	player.y = 400;
	player.w = 12;
	player.h = 12;
	player.a = PI3;
	player.dx = cos(player.a) * 5;
	player.dy = sin(player.a) * 5;
}
