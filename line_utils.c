/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:51:57 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 10:43:10 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		line_count(t_p2d p1, t_p2d p2)
{
	t_li	val;
	int		ct;

	init_line_stuffs(&val, p1, p2);
	ct = 0;
	while (1)
	{
		ct++;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
	return (ct);
}

void	line_col_usr(t_p2d p1, t_p2d p2, t_stuffs *s)
{
	t_li	val;
	int		id[2];
	t_rgb	col;
	t_rgb	from;
	t_rgb	to;

	if (p1.x == -1 || p2.x == -1 || p1.y == -1 || p2.x == -1)
		return ;
	init_line_stuffs(&val, p1, p2);
	id[0] = 0;
	id[1] = line_count(p1, p2);
	from = int_to_rgb(p1.color);
	to = int_to_rgb(p2.color);
	while (1)
	{
		col.red = from.red + ((to.red - from.red) / id[1]) * id[0];
		col.green = from.green + ((to.green - from.green) / id[1]) * id[0];
		col.blue = from.blue + ((to.blue - from.blue) / id[1]) * id[0];
		mlx_pixel_put(s->co, s->win, p1.x, p1.y, rgb_to_int(col));
		id[0]++;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
}

void	line_colu(t_p2d p1, t_p2d p2, t_stuffs *s)
{
	t_li	val;
	int		cpt;
	int		nbp;
	int		red;
	t_p2d	fto;

	if (p1.x == -1 || p2.x == -1 || p1.y == -1 || p2.x == -1)
		return ;
	init_line_stuffs(&val, p1, p2);
	cpt = 0;
	nbp = line_count(p1, p2);
	fto = set_fromto(s, p1, p2);
	while (1)
	{
		red = fto.y + ((fto.x - fto.y) / nbp) * cpt;
		mlx_pixel_put(s->co, s->win, p1.x, p1.y, get_color(0, red, 255 - red));
		cpt++;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
}

void	line_col(t_p2d p1, t_p2d p2, t_stuffs *s)
{
	if (s->hascolors)
		line_col_usr(p1, p2, s);
	else
		line_colu(p1, p2, s);
}
