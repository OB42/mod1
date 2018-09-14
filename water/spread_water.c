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

t_p2d g_neighbor[4] = {
	(t_p2d){.x = 1, .y = 0}, (t_p2d){.x = 0, .y = -1},
	(t_p2d){.x = 0, .y = 1}, (t_p2d){.x = -1, .y = 0}};

void	move_water(t_p2d *from, t_p2d *to, float quantity)
{
	from->elev -= quantity;
	to->elev += quantity;
}

void	gen_current_elev_map(float ***now, t_stuffs *s)
{
	int				e;
	int				w;

	if (!(*now))
	{
		*now = pr_malloc(sizeof(float*) * (s->size_x * s->linelen + 1));
		e = 0;
		while (e < ((s->size_x) * s->linelen))
			(*now)[e++] = pr_malloc(sizeof(float) *
											(s->size_y * s->linelen + 1));
	}
	e = 0;
	while (e < ((s->size_x) * s->linelen))
	{
		w = 0;
		while ((w < (s->size_y) * s->linelen))
		{
			(*now)[e][w] = s->water->bigmap[e][w].elev;
			w++;
		}
		e++;
	}
}

t_p2d	get_lowest_adjacent_point(t_stuffs *s, float **now, int e, int w)
{
	t_p2d			max;
	int				x;
	int				y;
	float			temp;
	int				i;

	i = 0;
	max = (t_p2d){.y = -1, .x = -1, .elev = 0};
	while (i < 4)
	{
		x = g_neighbor[i].x + e;
		y = g_neighbor[i].y + w;
		if (x > -1 && y > -1 && x < (s->size_x) * s->linelen
		&& y < (s->size_y) * s->linelen)
		{
			temp = (s->bigmap[e][w].elev + now[e][w]) -
											(s->bigmap[x][y].elev + now[x][y]);
			if (temp > max.elev)
				max = (t_p2d){.x = x, .y = y, .elev = temp};
		}
		i++;
	}
	return (max);
}

t_p2d	move_to_lowest_point(t_stuffs *s, float **now, t_p2d p, t_p2d max)
{
	int				x;
	int				y;
	float			temp;
	int				i;

	if (max.elev > 1 - 0.01)
	{
		i = -1;
		while (++i < 4)
		{
			x = g_neighbor[i].x + p.x;
			y = g_neighbor[i].y + p.y;
			if (x > -1 && y > -1 && x < (s->size_x) * s->linelen
			&& y < (s->size_y) * s->linelen)
			{
				temp = (s->bigmap[p.x][p.y].elev + now[p.x][p.y])
				- (s->bigmap[x][y].elev + now[x][y]);
				if (temp > max.elev * 0.99)
					move_water(&(s->water->bigmap[p.x][p.y]),
					&(s->water->bigmap[x][y]), 1);
			}
		}
	}
	return (max);
}

void	spread_water(t_stuffs *s)
{
	int				e;
	int				w;
	t_p2d			max;
	static float	**now = 0;

	gen_current_elev_map(&now, s);
	e = 0;
	while (e < ((s->size_x - 1) * s->linelen - 1))
	{
		w = 0;
		while (w < (s->size_y) * s->linelen)
		{
			if (s->water->bigmap[e][w].elev > 0.99)
			{
				max = get_lowest_adjacent_point(s, now, e, w);
				move_to_lowest_point(s, now, (t_p2d){.x = e, .y = w}, max);
			}
			w++;
		}
		e++;
	}
}
