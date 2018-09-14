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

void	wave(t_stuffs *stuffs)
{
	int	i;
	int	e;
	int	w;

	e = 0;
	usleep(stuffs->raining_intensity);
	gen_watermap(stuffs, 'W');
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while (w < ((stuffs->size_y) * stuffs->linelen))
			ft_triangle(stuffs, e, w++);
		e++;
	}
	i = 0;
	while (i++ < 100)
		spread_water(stuffs);
	redraw_water(stuffs);
}
