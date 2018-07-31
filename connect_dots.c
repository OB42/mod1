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

#include "fdf.h"

void	connect_fne_dots(t_stuffs *stuffs)
{
		int		e;
		int		w;
		int		color;

		e = 0 * stuffs->linelen;
		ft_printf("Rendering fine dots..\n");
		while (e < (stuffs->size_x * stuffs->linelen))
		{
			w = 0 * stuffs->linelen;
			while (w < (stuffs->size_y * stuffs->linelen))
			{

				if ((stuffs->bigmap)[e][w].elev >= 0 )
				{
					color = get_color_by_altitude(stuffs->bigmap[e][w].elev);
					t_p2d cheat;
					cheat = (stuffs->bigmap)[e][w];
					cheat.y += 16;
					line((stuffs->bigmap)[e][w], cheat, stuffs, color);
				}
				w++;
			}
			e++;
		}
		ft_printf("Done %i!\n", stuffs->linelen);
}

void	connect_fine_dots(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 0;
	ft_printf("Rendering fine dots...\n");
	//not sure
	while (e < ((stuffs->size_x - 1)* stuffs->linelen))
		{
			w = 0;
			//not sure
			while ((w < (stuffs->size_y - 1) * stuffs->linelen))
			{
				if (w != stuffs->size_y * stuffs->linelen)
				{
					if ((stuffs->bigmap)[e][w].x != 0 &&
							(stuffs->bigmap)[e][ w + stuffs->linelen - (w % stuffs->linelen)].x > 0 &&
							(stuffs->bigmap)[e][w].color != -1 &&
							(stuffs->bigmap)[e][ w + stuffs->linelen - (w % stuffs->linelen)].color != -1)
					{
						special_fine_line((stuffs->bigmap)[e][w],
								(stuffs->bigmap)[e][w + stuffs->linelen - (w %stuffs->linelen)],
								stuffs,
								(t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = w + stuffs->linelen - (w % stuffs->linelen) });
					}
				}
				if (e != stuffs->size_x)
				{
					if (
							(stuffs->bigmap)[e][w].x != 0 &&
							(stuffs->bigmap)[e + stuffs->linelen - (e % stuffs->linelen)][ w].x != 0 &&
					(stuffs->bigmap)[e][w].color != -1 &&
	(stuffs->bigmap)[e + stuffs->linelen - (e % stuffs->linelen)][ w].color != -1

					   )
					{
						special_fine_line((stuffs->bigmap)[e][w],
								(stuffs->bigmap)[e + stuffs->linelen - (e % stuffs->linelen)][w ]
								, stuffs,
								(t_coords){.x1 = e, .y1 = w, .x2 = e + stuffs->linelen - (e % stuffs->linelen), .y2 = w });
					}
				}
				w++;
			}
			e++;
		}
	ft_printf("Done !\n\n");
	connect_fne_dots(stuffs);
}

void	connect_dots(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 1;
	ft_printf("Rendering dots...\n");
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
	ft_printf("Done !\n\n");
	connect_fine_dots(stuffs);
}
