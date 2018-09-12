/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_water.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2018/09/12 16:04:51 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void		more_water(t_stuffs *stuffs, char mode)
{
	int e;
	int w;

	e = 1;
	while (e <= stuffs->size_x)
	{
		if (mode == 'R')
		{
			stuffs->watermap[e][1].n_elev += 0.15;
			stuffs->watermap[e][stuffs->size_y - 1].s_elev += 0.15;
		}
		else
			stuffs->watermap[e][1].n_elev += 0.8;
		w = 1;
		while (w <= stuffs->size_y && mode == 'R')
		{
			stuffs->watermap[1][w].e_elev += 0.15;
			stuffs->watermap[stuffs->size_x - 1][w].e_elev += 0.15;
			w++;
		}
		e++;
	}
}
