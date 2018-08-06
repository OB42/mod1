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
	int i;
	static	float	**previous = 0;
	static	float	**current = 0;
	static t_p2d n[4] = {
		(t_p2d){.x = 0, .y = 1},
		(t_p2d){.x = 0, .y = -1},
		(t_p2d){.x = 1, .y = 0},
		(t_p2d){.x = -1, .y = 0},
	};
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
	int dec = 1;
	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while (w < (stuffs->size_y) * stuffs->linelen)
		{
			if (stuffs->water->bigmap[e][w].elev > dec * 0.99)
			{
				max.y = -1;
				max.x = -1;
				max.elev = 0;
				i = 0;
				while (i < 4)
				{
					x = n[i].x + e;
					y = n[i].y + w;
					if (x > -1 && y > -1 && x < (stuffs->size_x) * stuffs->linelen && y < (stuffs->size_y) * stuffs->linelen)
					{
						temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[x][y].elev + current[x][y]);
						if (temp * 0.99 > max.elev)
						{
							max.x = x;
							max.y = y;
							max.elev = temp;
						}
					}
					i++;
				}
				if (max.elev > dec * 0.99)
				{
					i = 0;
					while (i < 4)
					{
						x = n[i].x + e;
						y = n[i].y + w;
						if (x > -1 && y > -1 && x < (stuffs->size_x) * stuffs->linelen && y < (stuffs->size_y) * stuffs->linelen)
						{
							temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[x][y].elev + current[x][y]);
							if (temp > max.elev * 0.99)
								move_water(stuffs, &(stuffs->water->bigmap[e][w]), &(stuffs->water->bigmap[x][y]), dec);
							if (max.elev < dec * 0.99)
							{
								break;
							}
						}
						i++;
					}
				}
			}
			w++;
		}
		e++;
	}
}

int water_loop(void *stuffs)
{
//	((t_stuffs *)stuffs)->raining = 1;
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
