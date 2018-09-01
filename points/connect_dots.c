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

void	rain_effect(t_stuffs *stuffs)
{
	int	r;
	int	l;
	int	e;
	int	w;
	int	i;

	e = 0;
	return;
	while (e < (stuffs->size_x * stuffs->linelen))
	{
		w = 0;
		while (w < (stuffs->size_y * stuffs->linelen))
		{
			if (stuffs->img.y + stuffs->bigmap[e][w].y)
			{
				if (w && rand() % stuffs->raining_intensity == 0)
				{
					r = rand() % (int)(stuffs->img.y + stuffs->bigmap[e][w].y);
					l = rand() % 7 + 3;
					i = 0;
					while (i < l)
					{
						set_pixel(stuffs->img.x + stuffs->bigmap[e][w].x, r - i, 0x00ccff, stuffs);
						i++;
					}
				}
			}
			w++;
		}
		e++;
	}
}

void	connect_fne_dots(t_stuffs *stuffs)
{
	int		e;
	int		w;
	int		color;
	int		i;
	static	int rain = 0;
	int		water;

	e = 0;
	while (e < (stuffs->size_x * stuffs->linelen))
	{
		w = 0;
		while (w < (stuffs->size_y * stuffs->linelen))
		{
			if ((stuffs->bigmap)[e][w].elev >= 0 )
			{
				water = (stuffs->water && stuffs->water->bigmap && stuffs->water->bigmap[e][w].elev > 0.1);
				color = water ? 0x00ccff : get_color_by_altitude(stuffs->bigmap[e][w].elev);
				// if (stuffs->bigmap[e][w].elev == 2.0)
				// {
				// 	color = 0xFF0000;
				// }
				t_p2d cheat;
				cheat = stuffs->bigmap[e][w];
				if ((e + 1 < stuffs->size_x * stuffs->linelen && !(stuffs->bigmap[e + 1][w].x)) ||
				(w + 1 < stuffs->size_y * stuffs->linelen && !(stuffs->bigmap[e][w +1 ].x)))
				{
					i = 1;
					while (i < 100)
					{
						set_pixel(stuffs->img.x + stuffs->bigmap[e][w].x - 1, stuffs->img.y + stuffs->bigmap[e][w].y + i, 0, stuffs);
						set_pixel(stuffs->img.x + stuffs->bigmap[e][w].x + 1, stuffs->img.y + stuffs->bigmap[e][w].y + i, 0, stuffs);
						set_pixel(stuffs->img.x + stuffs->bigmap[e][w].x, stuffs->img.y + stuffs->bigmap[e][w].y + i, 0, stuffs);
						i++;
					}
				}
				else if (water && (stuffs->bigmap)[e][w].y)
				{
					t_p2d temp = (stuffs->bigmap)[e][w];
					temp.elev += (stuffs->water->bigmap)[e][w].elev;
					temp.y -= (stuffs->water->bigmap)[e][w].elev * stuffs->coef;
					cheat = temp;
					cheat.y += temp.elev + 16;
					line(temp, cheat, stuffs, color);
				}
				else if (e < (stuffs->size_x * stuffs->linelen) && w < (stuffs->size_y * stuffs->linelen))
				{
					cheat.y += 16;
					line((stuffs->bigmap)[e][w], cheat, stuffs, color);
				}
			}
			w++;
		}
		e++;
	}
	if (stuffs->scenario == RAIN)
		rain_effect(stuffs);
}

int	get_next(int val, t_stuffs *stuffs)
{
	return (val + stuffs->linelen - (val % stuffs->linelen));
}

void	check_and_connect(t_stuffs *stuffs, int e, int w, char direction)
{
	t_p2d point_from;
	t_p2d point_to;
	t_coords co;
	int		temp;

	point_from = (stuffs->bigmap)[e][w];

	if (direction == 'y')
	{
		temp = get_next(w, stuffs);
		if (temp < (stuffs->size_y * stuffs->linelen))
		{
			point_to = (stuffs->bigmap)[e][get_next(w, stuffs)];
			co = (t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = get_next(w, stuffs)};
			if (point_from.x != 0 && point_to.x > 0)
				special_fine_line(point_from, point_to, stuffs,co);
		}
	}
	else
	{
		temp = get_next(e, stuffs);
		if (temp < (stuffs->size_x * stuffs->linelen))
		{
			point_to = (stuffs->bigmap)[get_next(e, stuffs)][w];
			co = (t_coords){.x1 = e, .y1 = w, .x2 = get_next(e, stuffs), .y2 = w};
			if (point_from.x != 0 && point_to.x > 0)
				special_fine_line(point_from, point_to, stuffs,co);
		}
	}
}


void	connect_fine_dots(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 0;
	//not sure
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		//not sure
		while ((w < (stuffs->size_y) * stuffs->linelen))
		{
			if (w < (stuffs->size_y * stuffs->linelen))
				check_and_connect(stuffs, e, w, 'y');
			if (e < (stuffs->size_x * stuffs->linelen))
				check_and_connect(stuffs, e, w, 'x');
			w++;
		}
		e++;
	}
	// ft_printf("Done !\n\n");
	connect_fne_dots(stuffs);
}

void	connect_dots(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 1;
	// ft_printf("Rendering dots...\n");
	while (e <= stuffs->size_x)
	{
		w = 1;
		while (w <= stuffs->size_y)
		{
			if (w != stuffs->size_y)
			{
				special_line((stuffs->map)[e][w], (stuffs->map)[e][w + 1], stuffs,
						(t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = w + 1});
			}
			if (e != stuffs->size_x)
			{
				special_line((stuffs->map)[e][w], (stuffs->map)[e + 1][w], stuffs,
						(t_coords){.x1 = e, .y1 = w, .x2 = e + 1, .y2 = w });
			}
			w++;
		}
		e++;
	}
	// ft_printf("Done !\n\n");
	connect_fine_dots(stuffs);
	w = (stuffs->size_y * stuffs->linelen);
}
