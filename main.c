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

#include "fdf.h"

void	init_img(t_stuffs *stuffs)
{
	printf("ok\n");
	stuffs->img.ptr = mlx_new_image(stuffs->co, WINX, WINY);
	printf("ok\n");
	stuffs->img.line_size = WINX * 4;
	stuffs->img.endian = 0;
	stuffs->img.bits_per_pixel = 32;
	stuffs->img.y = 0;
	stuffs->img.x = 0;
	stuffs->img.img_addr = mlx_get_data_addr(stuffs->img.ptr,
		&(stuffs->img.bits_per_pixel), &(stuffs->img.line_size), &(stuffs->img.endian));
}

int	main(int argc, char **argv)
{
	t_stuffs	stuffs;

	stuffs.hascolors = 0;
	stuffs.coef = 1;
	stuffs.linelen = -1;
	stuffs.ogcolors = 0;
	if (argc != 2)
	{
		ft_printf("Usage : ./fdf ./path/to/map/map.fdf\n");
		return (2);
	}
	if (exit_msg(file_feed(argv[1], &stuffs)))
		return (1);
	set_props(&stuffs);
	set_scale(&stuffs);
	malloc_map(&stuffs);
	stuffs.co = mlx_init();
	stuffs.win = mlx_new_window(stuffs.co, WINX, WINY, "Test");
	init_img(&stuffs);
	stuffs.altinfos.y = INT_MAX;
	stuffs.altinfos.x = INT_MIN;
	set_dots(&stuffs);
	connect_dots(&stuffs);
	mlx_key_hook(stuffs.win, &hook, &stuffs);
	mlx_loop(stuffs.co);
	return (0);
}
