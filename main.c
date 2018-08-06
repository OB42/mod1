/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/15 06:30:56 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	init_img(t_stuffs *stuffs)
{
	stuffs->img.ptr = mlx_new_image(stuffs->co, WINX, WINY);
	stuffs->img.line_size = WINX * 4;
	stuffs->img.endian = 0;
	stuffs->img.bits_per_pixel = 32;
	stuffs->img.y = 0;
	stuffs->img.x = 0;
	stuffs->img.img_addr = mlx_get_data_addr(stuffs->img.ptr,
		&(stuffs->img.bits_per_pixel), &(stuffs->img.line_size), &(stuffs->img.endian));
}

int	init(t_stuffs *stuffs, char *path)
{
	stuffs->coef = 1;
	stuffs->linelen = -1;
	stuffs->raining = 0;
	if (exit_msg(file_feed(path, stuffs)))
		return (1);
	set_props(stuffs);
	set_scale(stuffs);
	malloc_map(stuffs);
	if (stuffs->water)
	{
		stuffs->co = mlx_init();
		stuffs->win = mlx_new_window(stuffs->co, WINX, WINY, "Test");
		init_img(stuffs);
	}
	set_dots(stuffs);
	connect_dots(stuffs);
	return (0);
}

void	move_water(t_stuffs *stuffs, t_p2d *from, t_p2d *to, float quantity)
{

	from->elev -= quantity;
	// from->y += quantity * stuffs->coef;
	to->elev++;
	// to->y -= quantity * stuffs->coef;
}

void	spread_water(t_stuffs *stuffs)
{
	int		e;
	int		w;
	int		x;
	int		y;
	t_p2d	max;
	int		z = 0;
	static int r = 0;
	static	float	**previous = 0;
	static	float	**current = 0;
	float temp = 0;
	if (!previous)
	{
		previous = pr_malloc(sizeof(float*) * (stuffs->size_x * stuffs->linelen + 1));
		current = pr_malloc(sizeof(float*) * (stuffs->size_x * stuffs->linelen + 1));
		e = 0;
		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			previous[e] = pr_malloc(sizeof(float) * (stuffs->size_y * stuffs->linelen + 1));
			current[e] = pr_malloc(sizeof(float) * (stuffs->size_y * stuffs->linelen + 1));
			w = 0;
			while (w < 100)
			{
				stuffs->water->bigmap[e][w].elev += 25;
				w++;
			}
			e++;
		}
	}
	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while ((w < (stuffs->size_y) * stuffs->linelen))
		{
			// if (rand() % 16 == 0)
			// {
			// 	stuffs->water->bigmap[e][w].elev += 1;
			// }
			// previous[e][w] = stuffs->water->bigmap[e][w].elev;
			current[e][w] = stuffs->water->bigmap[e][w].elev;
			w++;
		}
		e++;
	}
	e = 0;
	while (z < 1)
	{
		e = 0;
		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;
			while (w < (stuffs->size_y) * stuffs->linelen)
			{
				if (stuffs->water->bigmap[e][w].elev > 0)
				{
					max.y = -1;
					max.x = -1;
					max.elev = 0;
					int sum = 0;
					x = -1;
					while (x < 2) {
						y = -1;
						while (y < 2) {
							if (!(!y && !x) && e + x > -1 && w + y > -1 && e + x < (stuffs->size_x) * stuffs->linelen && w + y < (stuffs->size_y) * stuffs->linelen)
							{
								if ((x == 0 && y == -1) || (x == -1 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 0))
								{
									temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[e + x][w + y].elev + current[e + x][w + y]);
									if (temp > max.elev)
									{
										max.x = e + x;
										max.y = w + y;
										max.elev = temp * 0.99;
									}
								}
							}
							y++;
						}
						x++;
					}
					x = -1;
					if (max.elev > 0.1)
					{
						while (x < 2) {
							y = -1;
							while (y < 2) {
								if (!(!y && !x) && e + x > -1 && w + y > -1 && e + x < (stuffs->size_x) * stuffs->linelen && w + y < (stuffs->size_y) * stuffs->linelen)
								{
									if ((x == 0 && y == -1) || (x == -1 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 0))
									{
										temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[e + x][w + y].elev + current[e + x][w + y]);
										if (temp >= max.elev)
										{
											move_water(stuffs, &(stuffs->water->bigmap[e][w]), &(stuffs->water->bigmap[e + x][w + y]), 1);
										}
									}
								}
								y++;
							}
							x++;
						}
					}

				//	stuffs->bigmap[e][w].y
				}
				w++;
			}
			e++;
		}
		z++;
	}
}

int water_loop(void *stuffs)
{
	((t_stuffs *)stuffs)->raining = 1;
	// add_water(stuffs);
	int i = 0;
	while (i < 100)
	{
		spread_water(stuffs);
		i++;
	}
	redraw(stuffs);
	return (0);
}

int		main(int argc, char **argv)
{
	t_stuffs	stuffs;
	t_stuffs	water;

	if (argc != 2)
	{
		ft_printf("Usage : ./mod1 ./path/to/map/map.mod1\n");
		return (2);
	}
	stuffs.water = &water;
	water.water = 0;
	if (init(&stuffs, argv[1]))
		return (1);
	water.co = stuffs.co;
	water.win = stuffs.win;
	if (init(&water, argv[1]))
		return (1);
	mlx_put_image_to_window(stuffs.co, stuffs.win, stuffs.img.ptr, 0, 0);
	mlx_loop_hook(stuffs.co, water_loop, &stuffs);
	// mlx_key_hook(stuffs.win, water_loop, &stuffs);
	mlx_loop(stuffs.co);
	return (0);
}
