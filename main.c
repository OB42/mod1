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
	stuffs.altinfos.y = INT_MAX;
	stuffs.altinfos.x = INT_MIN;
	set_dots(&stuffs);
	connect_dots(&stuffs);
	mlx_key_hook(stuffs.win, &hook, &stuffs);
	mlx_loop(stuffs.co);
	return (0);
}
