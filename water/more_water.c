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

void		more_water(t_stuffs *s, char mode)
{
	int	i;

	i = 1;
	if (mode == 'R')
	{
		while (i <= s->size_x)
		{
			s->watermap[i][1].n_elev += 2;
			s->watermap[i][s->size_y - 1].s_elev += 2;
			i++;
		}
		i = 1;
		while (i <= s->size_y)
		{
			s->watermap[1][i].e_elev += 2;
			s->watermap[s->size_x - 1][i].w_elev += 2;
			i++;
		}
	}
	else
	{
		i = 1;
		while (i <= s->size_y)
			s->watermap[s->size_x - 1][i++].s_elev += 2;
	}
}
