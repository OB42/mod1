/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spread_water.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/15 06:30:56 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	move_water(t_stuffs *s, t_p2d *from, t_p2d *to, float quantity)
{
	from->elev -= quantity;
	to->elev += quantity;
}

void	spread_water(t_stuffs *s)
{
	int				e;
	int				w;
	int				x;
	int				y;
	t_p2d			max;
	int				i;
	float	 		temp;
	static	float **now = 0;
	static t_p2d n[4] = {
		(t_p2d){.x = 1, .y = 0},
		(t_p2d){.x = 0, .y = -1},
		(t_p2d){.x = 0, .y = 1},
		(t_p2d){.x = -1, .y = 0},
	};

	temp = 0;
	if (!now)
	{
		now = pr_malloc(sizeof(float*) * (s->size_x * s->linelen + 1));
		e = 0;
		while (e < ((s->size_x) * s->linelen))
			now[e++] = pr_malloc(sizeof(float) * (s->size_y * s->linelen + 1));
	}
	e = 0;
	while (e < ((s->size_x) * s->linelen))
	{
		w = 0;
		while ((w < (s->size_y) * s->linelen))
		{
			now[e][w] = s->water->bigmap[e][w].elev;
			w++;
		}
		e++;
	}
	e = 0;
	while (e < ((s->size_x) * s->linelen))
	{
		w = 0;
		while (w < (s->size_y) * s->linelen)
		{
			if (s->water->bigmap[e][w].elev > 0.99)
			{
				max.y = -1;
				max.x = -1;
				max.elev = 0;
				i = 0;
				int multi = 0;
				while (i < 4)
				{
					x = n[i].x + e;
					y = n[i].y + w;
					if (x > -1 && y > -1 && x < (s->size_x) * s->linelen && y < (s->size_y) * s->linelen)
					{
						temp = (s->bigmap[e][w].elev + now[e][w]) - (s->bigmap[x][y].elev + now[x][y]);
						if (temp > max.elev)
							max = (t_p2d){.x = x, .y = y, .elev = temp};
					}
					i++;
				}
				if (max.elev > 1 - 0.01)
				{
					int d = multi ? 1 : 1 / (multi + 1);
					i = 0;
					while (i < 4)
					{
						x = n[i].x + e;
						y = n[i].y + w;
						if (x > -1 && y > -1 && x < (s->size_x) * s->linelen && y < (s->size_y) * s->linelen)
						{
							temp = (s->bigmap[e][w].elev + now[e][w]) - (s->bigmap[x][y].elev + now[x][y]);
							if (temp > max.elev * 0.99)
								move_water(s, &(s->water->bigmap[e][w]), &(s->water->bigmap[x][y]), 1);
						}
						i++;
					}
				}
			}
			w++;
		}
		e++;
	}
}
