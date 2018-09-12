/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rising_water.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	rising_water(t_stuffs * stuffs)
{
	int		e;
	int		w;
	t_p2d	tmp_a;
	t_p2d	tmp_b;
	t_p2d	tmp_c;

	e = 0;
	gen_watermap(stuffs, 'R');
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while (w < ((stuffs->size_y) * stuffs->linelen))
		{
			tmp_a = tmp_a;
			tmp_b = (t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w + (stuffs->linelen - (w % stuffs->linelen)))};
			tmp_c = (t_p2d){.x = (e - (e % stuffs->linelen) + (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) + (stuffs->linelen / 2))};
			if (point_inside_triangle((t_p2d){.x = e, .y = w}, tmp_a,
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w - (w % stuffs->linelen))},
						tmp_c))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].N_elev  - stuffs->bigmap[e][w].elev;
			}
			else if (point_inside_triangle((t_p2d){.x = e, .y = w}, tmp_b,
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w + (stuffs->linelen -(w % stuffs->linelen)))},
						tmp_c))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].S_elev  - stuffs->bigmap[e][w].elev;
			}
			else if (point_inside_triangle((t_p2d){.x = e, .y = w},
						tmp_a, tmp_b, tmp_c))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].E_elev  - stuffs->bigmap[e][w].elev;
			}
			else if (point_inside_triangle((t_p2d){.x = e, .y = w},
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w - (w % stuffs->linelen))},
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w + (stuffs->linelen -(w % stuffs->linelen)))},
						tmp_c))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].W_elev  - stuffs->bigmap[e][w].elev;
			}
			w++;
		}
		e++;
	}
	e = 0;
	while (e++ < 50)
		spread_water(stuffs);
	redraw_water(stuffs);
}
