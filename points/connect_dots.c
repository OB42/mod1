/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_dots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void	connect_fne_dots(t_stuffs *s)
{
	int		e;
	int		w;

	e = 0;
	while (e < (s->size_x * s->linelen))
	{
		w = 0;
		while (w < (s->size_y * s->linelen))
		{
			if ((s->bigmap)[e][w].elev >= 0)
				draw_dot(s, (t_p2d){.x = e, .y = w}, WATER);
			w++;
		}
		e++;
	}
	if (s->scenario == RAIN)
		rain_effect(s);
}

int		get_next(int val, t_stuffs *s)
{
	return (val + s->linelen - (val % s->linelen));
}

void	check_and_connect(t_stuffs *s, int e, int w, char direction)
{
	t_p2d		point_from;
	t_p2d		point_to;
	t_coords	co;
	int			temp;

	point_from = (s->bigmap)[e][w];
	if (direction == 'y' && (temp = get_next(w, s)) < (s->size_y * s->linelen))
	{
		point_to = (s->bigmap)[e][get_next(w, s)];
		co = (t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = get_next(w, s)};
		if (point_from.x != 0 && point_to.x > 0)
			special_fine_line(point_from, point_to, s, co);
	}
	else
	{
		if ((temp = get_next(e, s)) < (s->size_x * s->linelen))
		{
			point_to = (s->bigmap)[get_next(e, s)][w];
			co = (t_coords){.x1 = e, .y1 = w, .x2 = get_next(e, s), .y2 = w};
			if (point_from.x != 0 && point_to.x > 0)
				special_fine_line(point_from, point_to, s, co);
		}
	}
}

void	connect_fine_dots(t_stuffs *s)
{
	int e;
	int w;

	e = 0;
	ft_printf("Rendering fine dots...\n");
	while (e < ((s->size_x) * s->linelen))
	{
		w = 0;
		while ((w < (s->size_y) * s->linelen))
		{
			if (w < (s->size_y * s->linelen))
				check_and_connect(s, e, w, 'y');
			if (e < (s->size_x * s->linelen))
				check_and_connect(s, e, w, 'x');
			w++;
		}
		e++;
	}
	ft_printf("Done !\n\n");
	connect_fne_dots(s);
}

void	connect_dots(t_stuffs *s)
{
	int e;
	int w;

	e = 1;
	ft_printf("Rendering dots...\n");
	while (e <= s->size_x)
	{
		w = 1;
		while (w <= s->size_y)
		{
			if (w != s->size_y)
			{
				special_line((s->map)[e][w], (s->map)[e][w + 1], s,
						(t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = w + 1});
			}
			if (e != s->size_x)
			{
				special_line((s->map)[e][w], (s->map)[e + 1][w], s,
						(t_coords){.x1 = e, .y1 = w, .x2 = e + 1, .y2 = w });
			}
			w++;
		}
		e++;
	}
	connect_fine_dots(s);
}
