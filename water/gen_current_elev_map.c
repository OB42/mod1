/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_current_elev_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/15 06:30:56 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

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
