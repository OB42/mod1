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

void	move_water(t_stuffs *stuffs, t_p2d *from, t_p2d *to, float quantity)
{
	from->elev -= quantity;
	to->elev += quantity;
}

void	spread_water(t_stuffs *stuffs)
{
	int				e;
	int				w;
	int				x;
	int				y;
	t_p2d			max;
	int				i;
	float	 		temp;
	static	float **current = 0;
	static t_p2d n[4] = {
		(t_p2d){.x = 1, .y = 0},
		(t_p2d){.x = 0, .y = -1},
		(t_p2d){.x = 0, .y = 1},
		(t_p2d){.x = -1, .y = 0},
	};

	temp = 0;
	if (!current)
	{
		current = pr_malloc(sizeof(float*) *
								(stuffs->size_x * stuffs->linelen + 1));
		e = 0;
		while (e < ((stuffs->size_x) * stuffs->linelen))
			current[e++] = pr_malloc(sizeof(float) *
			(stuffs->size_y * stuffs->linelen + 1));
	}
	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while ((w < (stuffs->size_y) * stuffs->linelen))
		{
			current[e][w] = stuffs->water->bigmap[e][w].elev;
			w++;
		}
		e++;
	}
	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while (w < (stuffs->size_y) * stuffs->linelen)
		{
			if (stuffs->water->bigmap[e][w].elev > 0.99)
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
					if (x > -1 && y > -1 && x < (stuffs->size_x) * stuffs->linelen && y < (stuffs->size_y) * stuffs->linelen)
					{
						temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[x][y].elev + current[x][y]);
						if (temp > max.elev)
						{
							max.x = x;
							max.y = y;
							max.elev = temp;
						}
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
						if (x > -1 && y > -1 && x < (stuffs->size_x) * stuffs->linelen && y < (stuffs->size_y) * stuffs->linelen)
						{
							temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[x][y].elev + current[x][y]);
							if (temp > max.elev * 0.99)
								move_water(stuffs, &(stuffs->water->bigmap[e][w]), &(stuffs->water->bigmap[x][y]), 1);
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
