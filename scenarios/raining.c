/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2018/09/12 06:30:56 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	raining(t_stuffs *s)
{
	int			i;
	int			e;
	int			w;

	i = 0;
	usleep(s->raining_intensity);
	while (i++ < 200)
		spread_water(s);
	e = 0;
	{
		while (e < ((s->size_x) * s->linelen))
		{
			w = 0;
			while ((w < (s->size_y) * s->linelen))
			{
				if (s->raining_intensity
				&& rand() % (s->raining_intensity / 2 + 1) == 0)
					s->water->bigmap[e][w].elev += 1;
				w++;
			}
			e++;
		}
	}
	redraw(s);
}

void	rain_effect(t_stuffs *s)
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
			if (s->img.y + s->bigmap[e][w].y
				&& w && rand() % s->raining_intensity == 0)
			{
				r = rand() % (int)(s->img.y + s->bigmap[e][w].y);
				l = rand() % 7 + 3;
				i = 0;
				while (i < l)
					set_pixel(s->img.x + s->bigmap[e][w].x, r - i++, WATER, s);
			}
			w++;
		}
		e++;
	}
}
