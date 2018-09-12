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

void	wave(t_stuffs * stuffs)
{
	int	i;
	int	e;
	int	w;

	e = 0;
	gen_watermap(stuffs,'W');
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while (w < ((stuffs->size_y) * stuffs->linelen))
		{
			if (point_inside_triangle((t_p2d){.x = e, .y = w},
						(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w - (w % stuffs->linelen))},
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w - (w % stuffs->linelen))},
						(t_p2d){.x = (e - (e % stuffs->linelen) + (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) + (stuffs->linelen / 2))}
						))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].N_elev  - stuffs->bigmap[e][w].elev;
			}
			else if (point_inside_triangle((t_p2d){.x = e, .y = w},
						(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w + (stuffs->linelen - (w % stuffs->linelen)))},
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w + (stuffs->linelen -(w % stuffs->linelen)))},
						(t_p2d){.x = (e - (e % stuffs->linelen) + (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) + (stuffs->linelen / 2))}
						))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].S_elev  - stuffs->bigmap[e][w].elev;
			}
			else if (point_inside_triangle((t_p2d){.x = e, .y = w},
						(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w - (w % stuffs->linelen))},
						(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w + (stuffs->linelen - (w % stuffs->linelen)))},
						(t_p2d){.x = (e - (e % stuffs->linelen) + (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) + (stuffs->linelen / 2))}
						))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].E_elev  - stuffs->bigmap[e][w].elev;
			}
			else if (point_inside_triangle((t_p2d){.x = e, .y = w},
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w - (w % stuffs->linelen))},
						(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w + (stuffs->linelen -(w % stuffs->linelen)))},
						(t_p2d){.x = (e - (e % stuffs->linelen) + (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) + (stuffs->linelen / 2))}
						))
			{
				stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e / stuffs->linelen) + 1][(w / stuffs->linelen) + 1].W_elev  - stuffs->bigmap[e][w].elev;
			}
			w++;
		}
		e++;
	}
	i = 0;
	while (i++ < 50)
		spread_water(stuffs);
	redraw_water(stuffs);
}
