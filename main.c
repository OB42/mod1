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
	stuffs->raining_intensity = 100;
	stuffs->coef = 1;
	stuffs->raining = 0;
	stuffs->linelen = -1;
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
	to->elev += quantity;
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
	static	float	**current = 0;
	static t_p2d n[4] = {
		(t_p2d){.x = 1, .y = 0},
		(t_p2d){.x = 0, .y = -1},
		(t_p2d){.x = 0, .y = 1},
		(t_p2d){.x = -1, .y = 0},
	};
	float temp = 0;

	if (!current)
	{
		current = pr_malloc(sizeof(float*) * (stuffs->size_x * stuffs->linelen + 1));
		e = 0;
		while (e < ((stuffs->size_x) * stuffs->linelen))
			current[e++] = pr_malloc(sizeof(float) * (stuffs->size_y * stuffs->linelen + 1));
	}
	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while ((w < (stuffs->size_y) * stuffs->linelen))
		{
			current[e][w] = stuffs->water->bigmap[e][w].elev;
			w++;
		}
		e++;
	}
	float dec = 1;
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
				int multi = 0;
				while (i < 4)
				{
					x = n[i].x + e;
					y = n[i].y + w;
					if (x > -1 && y > -1 && x < (stuffs->size_x) * stuffs->linelen && y < (stuffs->size_y) * stuffs->linelen)
					{
						temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[x][y].elev + current[x][y]);
						if (temp > max.elev)
						{
							max.x = x;
							max.y = y;
							// if (temp < max.elev + 0.1)
							// 	multi++;
							// else
							// 	multi = 0;
							max.elev = temp;
						}
					}
					i++;
				}
				if (max.elev > dec - 0.01)
				{
					int d = multi ? dec : dec / (multi + 1);
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
							// if (stuffs->water->bigmap[e][w] < dec * 0.99)
							// {
							// 	break;
							// }
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

void	raining(t_stuffs *stuffs)
{
	int			i;
	int			e;
	int			w;
	static int r = 0;

	i = 0;
	while (i++ < 100)
		spread_water(stuffs);
	// if (!(r++))
	e = 0;
	{
		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;
			while ((w < (stuffs->size_y) * stuffs->linelen))
			{
				if (stuffs->raining_intensity && rand() % (stuffs->raining_intensity / 2 + 1) == 0)
					stuffs->water->bigmap[e][w].elev += 1;
				w++;
			}
			e++;
		}
	}
	redraw(stuffs);
	printf("ok\n");
}

void	rising_water(t_stuffs *stuffs)
{
	int			i;
	int			e;
	int			w;
	static int r = 0;

	i = 0;

	e = 16;
	w = 1;
	while ((w < (stuffs->size_y) * stuffs->linelen) - 1)
	{
		stuffs->water->bigmap[0][w].elev += 5;
		stuffs->water->bigmap[stuffs->size_x * stuffs->linelen - 1][w].elev += 5;
		w++;
	}
	while (i++ < 42)
		spread_water(stuffs);
	redraw(stuffs);
}

void	wave(t_stuffs *stuffs)
{
	int			i;
	int			e;
	int			w;
	static int r = 0;

	i = 0;
	e = 0;
	if (!r)
	{
		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;
			while (w < ((stuffs->size_y) * stuffs->linelen))
			{
				int	k =  1;
//				if (stuffs->bigmap[e][w].elev >= k)
	//				stuffs->bigmap[e][w].elev -= k;
				w++;
			}
			e++;
		}
		r = 1;
	}
//	if ((r++) % 2 == 0)
	{
		e = 0;
			//stuffs->water->bigmap[(stuffs->size_x) * stuffs->linelen - 32 - 1][0].elev += 100;
	//	 	stuffs->water->bigmap[0][0].elev += 10;

		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;
			while (w < 5 ||  stuffs->water->bigmap[e][w].elev > 0.1)
			{
				stuffs->water->bigmap[e][w].elev += 1;
				w++;
			}
			e++;
		}
	}
	while (i++ < 1000)
		spread_water(stuffs);
	e = 0;
	// if ((r++) % 4 == 0)



	redraw(stuffs);
}
int	water_loop(void *stuffs)
{
	if (((t_stuffs *)stuffs)->scenario == WAVE)
		wave(stuffs);
	else if (((t_stuffs *)stuffs)->scenario == RAIN)
		raining(stuffs);
	else if (((t_stuffs *)stuffs)->scenario == RISING_WATER)
		rising_water(stuffs);
	return (0);
}

void	usage()
{
	ft_printf("Usage : ./mod1 ./path/to/map/map.mod1 [scenario]\n");
	ft_printf("Scenarios:\n");
	ft_printf("0: Wave\n");
	ft_printf("1: Rain\n");
	ft_printf("2: Rising water\n");
	exit(2);
}

int		main(int argc, char **argv)
{
	t_stuffs	stuffs;
	t_stuffs	water;

	if (argc != 3)
		usage();
	if (argv[2][0] == '0')
		stuffs.scenario = WAVE;
	else if (argv[2][0] == '1')
		stuffs.scenario = RAIN;
	else if (argv[2][0] == '2')
		stuffs.scenario = RISING_WATER;
	else
		usage();
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
	mlx_key_hook(stuffs.win, hook, &stuffs);
	mlx_loop(stuffs.co);
	return (0);
}
