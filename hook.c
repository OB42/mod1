/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:51:42 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/15 06:29:54 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	redraw(t_stuffs *stu)
{
	clear(stu);
	set_dots(stu);
	connect_dots(stu);
	mlx_put_image_to_window(stu->co, stu->win, stu->img.ptr, 0, 0);
}

void	redraw_water(t_stuffs *stu)
{
	set_dots(stu);
	connect_water_dots(stu);
	mlx_put_image_to_window(stu->co, stu->win, stu->img.ptr, 0, 0);
}

void	free_stuffs(t_stuffs *stuffs)
{
	int e;

	e = 1;
	while (e <= stuffs->size_x)
	{
		free((stuffs->map)[e]);
		free((stuffs->elevs)[e]);
		e++;
	}
	free(stuffs->map);
	free(stuffs->elevs);
	exit(0);
}

int		hook(int keycode, void *stuffs)
{
	if (keycode == 53)
		free_stuffs(stuffs);
	if (keycode == 0x7C)
		((t_stuffs*)stuffs)->img.x += POS_INCREMENT;
	else if (keycode == 0x7B)
		((t_stuffs*)stuffs)->img.x -= POS_INCREMENT;
	else if (keycode == 0x7D)
		((t_stuffs*)stuffs)->img.y += POS_INCREMENT;
	else if (keycode == 0x7E)
		((t_stuffs*)stuffs)->img.y -= POS_INCREMENT;
	return (0);
}

int		exit_msg(int ret_code)
{
	if (!ret_code)
		return (0);
	else if (ret_code == -1)
		ft_printf(" -> File not found, aborting.\n");
	else if (ret_code == -2)
		ft_printf(" -> File exist but is incorrect in some way.\n");
	else if (ret_code > 0)
		ft_printf(" -> Incorrect line (%d) found in file, abort.\n", ret_code);
	return (1);
}
