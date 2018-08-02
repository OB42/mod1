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

#include "fdf.h"

void	redraw(t_stuffs *stu, int vp)
{
	clear(stu);
	stu->viewpoint = vp;
	set_dots(stu);
	connect_dots(stu);
	mlx_put_image_to_window(stu->co, stu->win, stu->img.ptr, 0, 0);
}

void	dirty_water_rising(t_stuffs *stuffs, int level)
{
	int e;
	int w;

	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
			w = 0;
			while ((w < (stuffs->size_y) * stuffs->linelen))
			{
				stuffs->water->bigmap[e][w].elev += level;
				stuffs->water->bigmap[e][w].y -= level * stuffs->coef;
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
			stuffs->water->map[e][w].elev += level;
			stuffs->water->map[e][w].y -= level * stuffs->coef;
			stuffs->water->elevs[e][w] += level;
			w++;
		}
		e++;
	}
}
void	free_stuffs(t_stuffs *stuffs)
{
	int e;

	e = 1;
	while (e <= stuffs->size_x)
	{
		free((stuffs->map)[e]);
		free((stuffs->elevs)[e]);
		if (stuffs->ogcolors)
			free((stuffs->colors)[e]);
		e++;
	}
	free(stuffs->map);
	free(stuffs->elevs);
	if (stuffs->ogcolors)
		free(stuffs->colors);
}

int		hook(int keycode, void *stuffs)
{
	if (keycode == 53)
	{
		free_stuffs(stuffs);
		exit(0);
	}
	clear(stuffs);
	if (keycode == 32)
		redraw(stuffs, 1);
	else if (keycode == 0x7C)
	{
		((t_stuffs*)stuffs)->img.x += POS_INCREMENT;
		redraw(stuffs, 1);
	}
	else if (keycode == 0x7B)
	{
		((t_stuffs*)stuffs)->img.x -= POS_INCREMENT;
		redraw(stuffs, 1);
	}
	else if (keycode == 0x7D)
	{
		((t_stuffs*)stuffs)->img.y += POS_INCREMENT;
		redraw(stuffs, 1);
	}
	else if (keycode == 0x7E)
	{
		((t_stuffs*)stuffs)->img.y -= POS_INCREMENT;
		redraw(stuffs, 1);
	}
	else if (keycode == 0x45)
	{
		dirty_water_rising(stuffs, 3);
		set_water(stuffs);
		redraw(stuffs, 1);
	}
	else if (keycode == 34)
		redraw(stuffs, 2);
	else if (keycode == 31)
		redraw(stuffs, 3);
	else if (keycode == 35)
		redraw(stuffs, 4);
	else if (keycode == 49)
	{
		if (((t_stuffs*)stuffs)->ogcolors)
			((t_stuffs*)stuffs)->hascolors = !((t_stuffs*)stuffs)->hascolors;
		redraw(stuffs, ((t_stuffs*)stuffs)->viewpoint);
	}
	else
		redraw(stuffs, ((t_stuffs*)stuffs)->viewpoint);
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
