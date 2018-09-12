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

void	rising_water(t_stuffs *stuffs)
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
			ft_triangle(stuffs, e, w++);
		e++;
	}
	e = 0;
	redraw_water(stuffs);
}
