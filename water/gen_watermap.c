/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_watermap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2018/09/12 16:04:51 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

t_cardinals	to_calc_between(t_stuffs *stuffs, int e, int w)
{
	t_cardinals cars;

	cars = (t_cardinals){.n = 0, .s = 0, .e = 0, .w = 0};
	if ((stuffs->scenario != WAVE || stuffs->size_x == e + 1)
		&& stuffs->watermap[e][w + 1].n_elev < stuffs->watermap[e][w].s_elev)
	{
		cars.s = 1;
	}
	if (w - 1 > 0
		&& stuffs->watermap[e][w - 1].s_elev < stuffs->watermap[e][w].n_elev)
	{
		cars.n = 1;
	}
	if (e + 1 < stuffs->size_x &&
		stuffs->watermap[e + 1][w].e_elev < stuffs->watermap[e][w].w_elev)
	{
		cars.w = 1;
	}
	if (e - 1 > 0 && e != stuffs->size_x
		&& stuffs->watermap[e - 1][w].w_elev < stuffs->watermap[e][w].e_elev)
		cars.e = 1;
	return (cars);
}

void		between_vertical(t_stuffs *stuffs, int e, int w, char dir)
{
	int		cc;
	float	*c1;
	float	*c2;
	t_p2d	coo;

	cc = 0;
	coo = (t_p2d){.x = e, .y = w};
	if (dir == 'S')
	{
		cc = 1;
		c1 = &(stuffs->watermap[e][w + cc].n_elev);
		c2 = &(stuffs->watermap[e][w].s_elev);
	}
	if (dir == 'N')
	{
		cc = -1;
		c1 = &(stuffs->watermap[e][w + cc].s_elev);
		c2 = &(stuffs->watermap[e][w].n_elev);
	}
	*(c1) += *(c2) * coef_between(stuffs, coo, dir, *(c2));
	if (*(c1) > *(c2))
		*(c1) = *(c2);
}

void		between_horiz(t_stuffs *stuffs, int e, int w, char dir)
{
	int		cc;
	float	*c1;
	float	*c2;
	t_p2d	coo;

	cc = 0;
	coo = (t_p2d){.x = e, .y = w};
	if (dir == 'W')
	{
		cc = 1;
		c1 = &(stuffs->watermap[e + cc][w].e_elev);
		c2 = &(stuffs->watermap[e][w].w_elev);
	}
	if (dir == 'E')
	{
		cc = -1;
		c1 = &(stuffs->watermap[e + cc][w].w_elev);
		c2 = &(stuffs->watermap[e][w].e_elev);
	}
	*(c1) += *(c2) * coef_between(stuffs, coo, dir, *(c2));
	if (*(c1) > *(c2))
		*(c1) = *(c2);
}

void		water_between(t_stuffs *stuffs, int e, int w)
{
	t_cardinals cars;

	cars = to_calc_between(stuffs, e, w);
	if (cars.s)
		between_vertical(stuffs, e, w, 'S');
	if (cars.n)
		between_vertical(stuffs, e, w, 'N');
	if (cars.w)
		between_horiz(stuffs, e, w, 'W');
	if (cars.e)
		between_horiz(stuffs, e, w, 'E');
}

void		gen_watermap(t_stuffs *stuffs, char mode)
{
	int		e;
	int		w;

	e = 1;
	more_water(stuffs, mode);
	while (e <= stuffs->size_x)
	{
		w = 1;
		while (w <= stuffs->size_y)
		{
			water_inside(stuffs, e, w);
			water_between(stuffs, e, w);
			w++;
		}
		e++;
	}
}
