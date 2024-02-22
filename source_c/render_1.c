#include "../headers/main.h"

/**
 * render_player - function that renders player
 * @instance: sdl instance
 *
 **/
void render_player(SDL_Instance instance)
{
	/* variables for the intial & finall beg. and end. coord. for SDL_rect */
	SDL_Rect rect;
	float x0, y0, x1, y1;

	/* Translate the player's position to map coordinates */
	rect.x = player.x * MAP_SCALE, rect.y = player.y * MAP_SCALE;
	rect.w = player.w * MAP_SCALE, rect.h = player.w * MAP_SCALE;
	/* render the player's rectangle */
	SDL_SetRenderDrawColor(instance.ren, 255, 255, 0, 0);
	SDL_RenderFillRect(instance.ren, &rect);

	/* render players line of sight */
	x0 = player.x * MAP_SCALE;
	y0 = player.y * MAP_SCALE;
	x1 = (player.x + player.dx * 20) * MAP_SCALE;
	y1 = (player.y + player.dy * 20) * MAP_SCALE;
	SDL_RenderDrawLine(instance.ren, x0, y0, x1, y1);
}

/**
 * render_map - function for rendering map
 * @ins: the given SDL instance
 *
 **/
void render_map(SDL_Instance ins)
{
	/* Variables for the x and y coordinates of the map:mapX mapY */
	int x, y;
	SDL_Rect rect;

	for (x = 0; x < map_x; x++)
	{
		for (y = 0; y < map_y; y++)
		{
			/* Set the wall color to white and empty space to black */
			if (getmap_value(y, x, 0) > 0)
				SDL_SetRenderDrawColor(ins.ren, 255, 255, 255, 0);
			else
				SDL_SetRenderDrawColor(ins.ren, 0, 0, 0, 0);
			/* Render the minmized map */
			rect.x = (y * map_s * MAP_SCALE) + 1;
			rect.y = (x * map_s * MAP_SCALE) + 1;
			rect.w = (map_s * MAP_SCALE) - 1;
			rect.h = (map_s * MAP_SCALE) - 1;
			SDL_RenderFillRect(ins.ren, &rect);
		}
	}
}

/**
 * render_scene - render scene function
 * @ins: given instance
 * @n: ray number
 * @h: height
 * @ray_a: the angle of the ray
 * @shd: the shade value
 * @rx: coordinate of the ray x_value
 * @ry: coordinate of the ray y_value
 * @m_txr: texture value of map
 *
 **/
void render_scene(SDL_Instance ins, int n, float h, float ray_a, float shd,
		float rx, float ry, int m_txr)
{
	/* rendering wall variables */
	float line, a = FixAng(player.a - ray_a), of, tx_y = 0, tx_x, tx_s, c;
	int j, i, idx, s = (int) SCREEN_WIDTH / 60;

	h = h * cos(a), line = (map_s * 420) / h, tx_s = 32.0 / (float)line;
	/* line offset in line limit */
	of = 280 - (line / 2);
	if (line > 420)
		line = 420, tx_y = (line - 420) / 2.0;
	tx_y = (tx_y * tx_s) + (m_txr * 32);
	/* shade the wall if it is 1 */
	if (shd == 1)
	{
		tx_x = (int) (rx / 2.0) % 32;
		if (ray_a > PI)
			tx_x = 31 - tx_x;
	}
	else
	{
		tx_x = (int) (ry / 2.0) % 32;
		if (ray_a > PI2 && ray_a < PI3)
			tx_x = 31 - tx_x;
	}
	/* render wall with above specification */
	for (i = 0; i < line; i++)
	{
		idx = (int)(tx_y) * 32 + (int)tx_x, c = (get_texture(idx) * 255) * shd;
		if (m_txr == 0)
			SDL_SetRenderDrawColor(ins.ren, c, c / 1.0, c / 1.0, 0);
		if (m_txr == 1)
			SDL_SetRenderDrawColor(ins.ren, c, c, c / 1.0, 0);
		if (m_txr == 2)
			SDL_SetRenderDrawColor(ins.ren, c / 1.0, c / 1.0, c, 0);
		if (m_txr == 3)
			SDL_SetRenderDrawColor(ins.ren, c / 1.0, c, c / 1.0, 0);
		for (j = n * s; j < (n * s) + s; j++)
			SDL_RenderDrawPoint(ins.ren, j, i + of);
		tx_y += tx_s;
	}
	render_floor(ins, of, n, line, ray_a); /** draw the ceiling **/
}
/**
 * render_floor - render floor function
 * @ln_off: the line offset
 * @line: the vertical line
 * @ra: the ray angle
 * @n: the index of each ray
 * @ins: the given instance
 *
 **/
void render_floor(SDL_Instance ins, float ln_off, int n, float line, float ra)
{
	/* rendernig floor variables */
	int i, j, idx, s = (int) SCREEN_WIDTH / 60;
	float dy, fix, tx_x, tx_y, clr, pa = player.a;

	/* Begin rendering the floor from where the wall ends */
	for (i = ln_off + line; i < SCREEN_HEIGHT; i++)
	{
		dy = i - (520 / 2.0), fix = cos(FixAng(pa - ra));
		tx_x = player.x / 2.0 + cos(ra) * 158 * 32 / dy / fix;
		tx_y = player.y / 2.0 - sin(ra) * 158 * 32 / dy / fix;
		idx = ((int)(tx_y) & 31) * 32 + ((int)(tx_x) & 31);
		clr = (get_texture(idx) * 255) * 0.9;
		SDL_SetRenderDrawColor(ins.ren, clr / 1.3, clr / 1.3, clr, 0);
		for (j = n * s; j < (n * s) + s; j++)
			SDL_RenderDrawPoint(ins.ren, j, i);
	}
}

/**
 * render_roof - render roof function)
 * @ln_off: the line offset
 * @line: the vertical line
 * @ra: the ray angle
 * @ins: the given instance
 * @n: the index of each ray
 *
 **/
void render_roof(SDL_Instance ins, float ln_off, int n, float line, float ra)
{
	/* rendering ceiling variables */
	int i, j, idx;
	float dy, fix, tx_x, tx_y, c, pa = player.a;

	/* Begin drawing the ceiling from the beginning up to the wall */
	for (i = ln_off + line; i < 500; i++)
	{
		dy = i - (500 / 2.0), fix = cos(FixAng(pa - ra));
		tx_x = player.x / 2.0 + cos(ra) * 158 * 32 / dy / fix;
		tx_y = player.y / 2.0 - sin(ra) * 158 * 32 / dy / fix;
		idx = ((int)(tx_y) & 31) * 32 + ((int)(tx_x) & 31);
		c = (get_texture(idx) * 255) * 0.7;
		SDL_SetRenderDrawColor(ins.ren, c / 3, c / 3, c / 3, 0);
		for (j = n * 8; j < (n * 8) + 8; j++)
			SDL_RenderDrawPoint(ins.ren, j + 530, 500 - i);
	}
}

