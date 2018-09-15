/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"
void	spread_wave(t_stuffs *s, int ig);

int	ignore(t_stuffs *s)
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
			if (s->water->bigmap[e][w].elev > 0.1)
			{
				return e + 42;
			}
			w++;
		}
		e++;
	}
	return (((s->size_x - 1) * s->linelen - 1));
}


void	wave(t_stuffs *stuffs)
{
	int	i;
	int	e;
	int	w;

	e = 0;
	usleep(stuffs->speed);
	gen_watermap(stuffs, 'W');
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while (w < ((stuffs->size_y) * stuffs->linelen))
			ft_triangle(stuffs, e, w++);
		e++;
	}
	i = 0;
	int ig = ignore(stuffs);
	while (i++ < 42)
		spread_wave(stuffs, ig);
	redraw_water(stuffs);
}
