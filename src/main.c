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
			&(stuffs->img.bits_per_pixel), &(stuffs->img.line_size),
			&(stuffs->img.endian));
}

int		init(t_stuffs *stuffs, char *path)
{
	stuffs->raining_intensity = 128;
	stuffs->speed = 0;
	stuffs->coef = 1;
	stuffs->raining = 0;
	stuffs->linelen = -1;
	gen_map(path, stuffs);
	set_props(stuffs);
	set_scale(stuffs);
	malloc_map(stuffs);
	malloc_watermap(stuffs);
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

int		water_loop(void *s)
{
	t_stuffs	*stuffs;
	int			e;
	int			w;

	stuffs = (t_stuffs *)s;
	e = 0;
	while (e < (stuffs->size_x * stuffs->linelen))
	{
		w = 0;
		while (w < (stuffs->size_y * stuffs->linelen))
		{
			if (stuffs->bigmap[e][w].elev <= 2.1)
				stuffs->bigmap[e][w].elev = 0;
			w++;
		}
		e++;
	}
	if (stuffs->scenario == WAVE)
		wave(stuffs);
	else if (stuffs->scenario == RAIN)
		raining(stuffs);
	else if (stuffs->scenario == RISING_WATER)
		rising_water(stuffs);
	return (0);
}

void	usage(void)
{
	ft_printf("Usage : ./ mod1 ./path/to/map.mod1 [scenario]\n");
	ft_printf("Scenarios:\n");
	ft_printf("0: Wave\n");
	ft_printf("1: Rain\n");
	ft_printf("2: Rising water\n");
	ft_printf("3: No water\n");
	exit(2);
}

int		main(int argc, char **argv)
{
	t_stuffs	stuffs;
	t_stuffs	water;

	stuffs = (t_stuffs){.water = &water, .water_lvl = 0};
	if (argc != 3 || ft_strcmp(INPUT_EXTENSION, argv[1] + ft_strlen(argv[1])
											- ft_strlen(INPUT_EXTENSION)))
		usage();
	if (argv[2][0] == '0')
		stuffs.scenario = WAVE;
	else if (argv[2][0] == '1')
		stuffs.scenario = RAIN;
	else if (argv[2][0] == '2')
		stuffs.scenario = RISING_WATER;
	else if (argv[2][0] == '3')
		stuffs.scenario = -1;
	else
		usage();
	water = (t_stuffs){.water = 0, .co = stuffs.co, .win = stuffs.win};
	if (init(&stuffs, argv[1]) || init(&water, argv[1]))
		return (1);
	mlx_put_image_to_window(stuffs.co, stuffs.win, stuffs.img.ptr, 100, 1100);
	mlx_loop_hook(stuffs.co, water_loop, &stuffs);
	mlx_key_hook(stuffs.win, hook, &stuffs);
	mlx_loop(stuffs.co);
	return (0);
}
