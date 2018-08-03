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

void set_water(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 0;
	printf("ok %i %i %i\n", stuffs->size_x, stuffs->size_y, stuffs->linelen);
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
			w = 0;
			while ((w < (stuffs->size_y) * stuffs->linelen))
			{
				if (stuffs->water->bigmap[e][w].elev > stuffs->bigmap[e][w].elev)
				{
					stuffs->bigmap[e][w] = stuffs->water->bigmap[e][w];
					stuffs->bigmap[e][w].is_water = 1;
				}
				w++;
			}
			e++;
	}

	e = 1;
	while (e <= stuffs->size_x)
	{
		w = 1;
		while (w <= stuffs->size_y)
		{
			 if ((stuffs->water->map)[e][w].elev > (stuffs->map)[e][w].elev)
			 {
				 	stuffs->map[e][w] = stuffs->water->map[e][w];
					stuffs->map[e][w].is_water = 1;
			}
			w++;
		}
		e++;
	}
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
	set_water(&stuffs);
	mlx_put_image_to_window(stuffs.co, stuffs.win, stuffs.img.ptr, 0, 0);
	mlx_key_hook(stuffs.win, &hook, &stuffs);
	mlx_loop(stuffs.co);
	return (0);
}
