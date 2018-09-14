/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void	draw_water(t_stuffs *s, t_p2d cheat, t_p2d p, int color)
{
	t_p2d	temp;

	temp = (s->bigmap)[p.x][p.y];
	temp.elev += (s->water->bigmap)[p.x][p.y].elev;
	temp.y -= (s->water->bigmap)[p.x][p.y].elev * s->coef;
	cheat = temp;
	cheat.y += temp.elev + 16;
	line(temp, cheat, s, color);
}

void	hide_borders(t_stuffs *s, t_p2d p)
{
	int	i;

	i = 0;
	if ((p.x + 1 < s->size_x * s->linelen && !(s->bigmap[p.x + 1][p.y].x))
	|| (p.y + 1 < s->size_y * s->linelen && !(s->bigmap[p.x][p.y + 1].x)))
	{
		i = 1;
		while (i < 32)
		{
			set_pixel(s->img.x + s->bigmap[p.x][p.y].x - 1,
				s->img.y + s->bigmap[p.x][p.y].y + i, 0, s);
			set_pixel(s->img.x + s->bigmap[p.x][p.y].x + 1,
				s->img.y + s->bigmap[p.x][p.y].y + i, 0, s);
			set_pixel(s->img.x + s->bigmap[p.x][p.y].x,
				s->img.y + s->bigmap[p.x][p.y].y + i, 0, s);
			i++;
		}
	}
}

void	draw_dot(t_stuffs *s, t_p2d p, int color)
{
	int		is_water;
	t_p2d	cheat;

	is_water = (s->water && s->water->bigmap
		&& s->water->bigmap[p.x][p.y].elev > 0.1);
	cheat = s->bigmap[p.x][p.y];
	cheat.y += 16;
	line((s->bigmap)[p.x][p.y], cheat, s,
	get_color_by_altitude(s->bigmap[p.x][p.y].elev));
	if (is_water && (s->bigmap)[p.x][p.y].y)
		draw_water(s, cheat, p, color);
	hide_borders(s, p);
}
