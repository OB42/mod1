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

void	raining(t_stuffs *stuffs)
{
	int			i;
	int			e;
	int			w;
	static int r = 0;

	i = 0;
	while (i++ < 100)
		spread_water(stuffs);
	e = 0;
	{
		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;
			while ((w < (stuffs->size_y) * stuffs->linelen))
			{
				if (stuffs->raining_intensity
				&& rand() % (stuffs->raining_intensity / 2 + 1) == 0)
					stuffs->water->bigmap[e][w].elev += 1;
				w++;
			}
			e++;
		}
	}
	redraw(stuffs);
}

void	rain_effect(t_stuffs *stuffs)
{
	int	r;
	int	l;
	int	e;
	int	w;
	int	i;

	e = 0;
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
						set_pixel(stuffs->img.x + stuffs->bigmap[e][w].x, r - i,
							0x00ccff, stuffs);
						i++;
					}
				}
			}
			w++;
		}
		e++;
	}
}
