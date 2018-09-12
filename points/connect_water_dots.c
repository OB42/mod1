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

void	w_rain_effect(t_stuffs *s)
{
	int	r;
	int	l;
	int	e;
	int	w;
	int	i;

	e = 0;
	while (e < (s->size_x * s->linelen))
	{
		w = 0;
		while (w < (s->size_y * s->linelen))
		{
			if (s->img.y + s->bigmap[e][w].y)
			{
				if (w && rand() % s->raining_intensity == 0)
				{
					r = rand() % (int)(s->img.y + s->bigmap[e][w].y);
					l = rand() % 7 + 3;
					i = 0;
					while (i < l)
					{
						set_pixel(s->img.x + s->bigmap[e][w].x, r - i, WATER, s);
						i++;
					}
				}
			}
			w++;
		}
		e++;
	}
}

void	w_connect_fne_dots(t_stuffs *s)
{
	int		e;
	int		w;
	int		i;
	int		water;
	t_p2d	cheat;

	e = 0;
	ft_printf("Rendering fine dots..\n");
	while (e < (s->size_x * s->linelen))
	{
		w = 0;
		while (w < (s->size_y * s->linelen))
		{
			if ((s->bigmap)[e][w].elev >= 0)
			{
				water = (s->water && s->water->bigmap && s->water->bigmap[e][w].elev > 0.1);
				cheat = s->bigmap[e][w];
				if ((e + 1 < s->size_x * s->linelen && !(s->bigmap[e + 1][w].x)) ||
						(w + 1 < s->size_y * s->linelen && !(s->bigmap[e][w +1 ].x)))
				{
					i = 1;
					while (i < 100)
					{
						set_pixel(s->img.x + s->bigmap[e][w].x - 1, s->img.y + s->bigmap[e][w].y + i, 0, s);
						set_pixel(s->img.x + s->bigmap[e][w].x + 1, s->img.y + s->bigmap[e][w].y + i, 0, s);
						set_pixel(s->img.x + s->bigmap[e][w].x, s->img.y + s->bigmap[e][w].y + i, 0, s);
						i++;
					}
				}
				cheat.y += 16;
				line((s->bigmap)[e][w], cheat, s, get_color_by_altitude(s->bigmap[e][w].elev));
				if (water && (s->bigmap)[e][w].y)
				{
					t_p2d temp = (s->bigmap)[e][w];
					temp.elev += (s->water->bigmap)[e][w].elev;
					temp.y -= (s->water->bigmap)[e][w].elev * s->coef;
					cheat = temp;
					cheat.y += temp.elev + 16;
					line(temp, cheat, s, 0x8000ccff);
				}
			}
			w++;
		}
		e++;
	}
	w = 0;

	if (s->scenario == RAIN)
		w_rain_effect(s);
}

int	w_get_next(int val, t_stuffs *s)
{
	return (val + s->linelen - (val % s->linelen));
}

void	w_check_and_connect(t_stuffs *s, int e, int w, char direction)
{
	t_p2d point_from;
	t_p2d point_to;
	t_coords co;
	int		temp;

	point_from = (s->bigmap)[e][w];

	if (direction == 'y')
	{
		temp = w_get_next(w, s);
		if (temp < (s->size_y * s->linelen))
		{
			point_to = (s->bigmap)[e][w_get_next(w, s)];
			co = (t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = w_get_next(w, s)};
			if (point_from.x != 0 && point_to.x > 0)
				special_fine_line(point_from, point_to, s,co);
		}
	}
	else
	{
		temp = w_get_next(e, s);
		if (temp < (s->size_x * s->linelen))
		{
			point_to = (s->bigmap)[w_get_next(e, s)][w];
			co = (t_coords){.x1 = e, .y1 = w, .x2 = w_get_next(e, s), .y2 = w};
			if (point_from.x != 0 && point_to.x > 0)
				special_fine_line(point_from, point_to, s,co);
		}
	}
}


void	w_connect_fine_dots(t_stuffs *s)
{

	/*
	int e;
	int w;

	e = 0;

	ft_printf("Rendering water fine dots...\n");
	ft_printf("water_lvl : %d\n", s->water_lvl);
	//not sure
	while (e < ((s->size_x) * s->linelen))
	{
		w = 0;
		//not sure
		while ((w < (s->size_y) * s->linelen))
		{
			if (s->water->bigmap[e][w].elev > 1 &&
			 s->water->bigmap[e][w].elev +100 < s->water_lvl)
			{
				if (w < (s->size_y * s->linelen))
				{
					// printf("a\n");
					w_check_and_connect(s, e, w, 'y');
					// printf("b\n");
				}
				if (e < (s->size_x * s->linelen))
				{
					// printf("c\n");
					w_check_and_connect(s, e, w, 'x');
					// printf("d\n");
				}
			}
			w++;
		}
		e++;
	}
	ft_printf("Done !\n\n");
*/
	w_connect_fne_dots(s);
}

void	connect_water_dots(t_stuffs *s)
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
	ft_printf("Done !\n\n");
	w_connect_fine_dots(s);
	w = (s->size_y * s->linelen);
}
