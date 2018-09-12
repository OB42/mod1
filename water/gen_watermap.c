/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_watermap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/15 06:30:56 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	more_water(t_stuffs *stuffs, char mode)
{
	int e;
	int w;

	e = 1;
	while (e <= stuffs->size_x)
	{
		if (mode == 'R')
		{
			stuffs->watermap[e][1].N_elev +=  0.1;
			stuffs->watermap[e][stuffs->size_y - 1].S_elev +=  0.1;
		}
		else
			stuffs->watermap[e][1].N_elev +=  0.8;
		w = 1;
		while (w <= stuffs->size_y && mode == 'R')
		{
			stuffs->watermap[1][w].E_elev +=  0.1;
			stuffs->watermap[stuffs->size_x - 1][w].E_elev +=  0.1;
			w++;
		}
		e++;
	}
}

t_cardinals	to_calc_between(t_stuffs *stuffs, int e, int w)
{
	t_cardinals cars;

	cars = (t_cardinals){.n = 0, .s = 0, .e = 0, .w = 0};
	if (w + 1 <= stuffs->size_y
		&& stuffs->watermap[e][w + 1].N_elev < stuffs->watermap[e][w].S_elev)
	{
		cars.s = 1;
	}
	if (w - 1 > 0
		&& stuffs->watermap[e][w - 1].S_elev < stuffs->watermap[e][w].N_elev)
	{
		cars.n = 1;
	}
	if (e + 1 < stuffs->size_x &&
		stuffs->watermap[e + 1][w].E_elev < stuffs->watermap[e][w].W_elev)
	{
		cars.w = 1;
	}
	if (e - 1 > 0 && e != stuffs->size_x && stuffs->watermap[e - 1][w].W_elev <  stuffs->watermap[e][w].E_elev)
		cars.e = 1;
	return (cars);
}

void	water_between (t_stuffs *stuffs, int e, int w)
{
	t_cardinals cars;

	cars = to_calc_between(stuffs, e, w);
	if (cars.s)
	{
		stuffs->watermap[e][w + 1].N_elev +=
			stuffs->watermap[e][w].S_elev *
			coef_between(stuffs, (t_p2d){.x = e, .y = w},'S', stuffs->watermap[e][w].S_elev);
		if (stuffs->watermap[e][w + 1].N_elev > stuffs->watermap[e][w].S_elev)
			stuffs->watermap[e][w + 1].N_elev = stuffs->watermap[e][w].S_elev;
	}
	if (cars.n)
	{
		stuffs->watermap[e][w - 1].S_elev +=
			stuffs->watermap[e][w].N_elev *
			coef_between(stuffs, (t_p2d){.x = e, .y = w},'N', stuffs->watermap[e][w].N_elev);
		if (stuffs->watermap[e][w - 1].S_elev > stuffs->watermap[e][w].N_elev)
			stuffs->watermap[e][w - 1].S_elev = stuffs->watermap[e][w].N_elev;

	}
	if (cars.w)
	{
		stuffs->watermap[e + 1][w].E_elev += stuffs->watermap[e][w].W_elev
			* coef_between(stuffs, (t_p2d){.x = e, .y = w},'W', stuffs->watermap[e][w].W_elev);
		if (stuffs->watermap[e + 1][w].E_elev > stuffs->watermap[e][w].W_elev)
			stuffs->watermap[e + 1][w].E_elev = stuffs->watermap[e][w].W_elev;
	}
	if (cars.e)
	{
		stuffs->watermap[e - 1][w].W_elev += stuffs->watermap[e][w].E_elev
			* coef_between(stuffs, (t_p2d){.x = e, .y = w},'E', stuffs->watermap[e][w].E_elev);
		if (stuffs->watermap[e - 1][w].W_elev > stuffs->watermap[e][w].E_elev)
			stuffs->watermap[e - 1][w].W_elev = stuffs->watermap[e][w].E_elev;
	}
}

void	water_inside(t_stuffs *stuffs, int e, int w)
{
	if (stuffs->watermap[e][w].W_elev < stuffs->watermap[e][w].N_elev)
	{
		stuffs->watermap[e][w].W_elev +=
			(stuffs->watermap[e][w].N_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'N', .y = 'W'}, stuffs->watermap[e][w].N_elev));
		if (stuffs->watermap[e][w].W_elev > stuffs->watermap[e][w].N_elev)
			stuffs->watermap[e][w].W_elev = stuffs->watermap[e][w].N_elev;
	}
	if (stuffs->watermap[e][w].W_elev < stuffs->watermap[e][w].S_elev)
	{
		stuffs->watermap[e][w].W_elev +=
			(stuffs->watermap[e][w].S_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'S', .y = 'W'}, stuffs->watermap[e][w].S_elev));
		if (stuffs->watermap[e][w].W_elev > stuffs->watermap[e][w].S_elev)
			stuffs->watermap[e][w].W_elev = stuffs->watermap[e][w].S_elev;
	}
	if (stuffs->watermap[e][w].S_elev < stuffs->watermap[e][w].E_elev)
	{
		stuffs->watermap[e][w].S_elev +=
			(stuffs->watermap[e][w].E_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'E', .y = 'S'}, stuffs->watermap[e][w].E_elev));
		if ((stuffs->watermap[e][w].S_elev > stuffs->watermap[e][w].E_elev))
			stuffs->watermap[e][w].S_elev = stuffs->watermap[e][w].E_elev;
	}
	if (stuffs->watermap[e][w].S_elev < stuffs->watermap[e][w].W_elev)
	{
		stuffs->watermap[e][w].S_elev +=
			(stuffs->watermap[e][w].W_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'W', .y = 'S'}, stuffs->watermap[e][w].W_elev));
		if ((stuffs->watermap[e][w].S_elev > stuffs->watermap[e][w].W_elev))
			stuffs->watermap[e][w].S_elev = stuffs->watermap[e][w].W_elev;
	}
	if (stuffs->watermap[e][w].E_elev < stuffs->watermap[e][w].N_elev)
	{
		stuffs->watermap[e][w].E_elev +=
			(stuffs->watermap[e][w].N_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'N', .y = 'E'}, stuffs->watermap[e][w].N_elev));
		if (stuffs->watermap[e][w].E_elev > stuffs->watermap[e][w].N_elev)
			stuffs->watermap[e][w].E_elev = stuffs->watermap[e][w].N_elev;

	}

	if (stuffs->watermap[e][w].E_elev < stuffs->watermap[e][w].S_elev)
	{
		stuffs->watermap[e][w].E_elev +=
			(stuffs->watermap[e][w].S_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'S', .y = 'E'}, stuffs->watermap[e][w].S_elev));
		if (stuffs->watermap[e][w].E_elev > stuffs->watermap[e][w].S_elev)
			stuffs->watermap[e][w].E_elev = stuffs->watermap[e][w].S_elev;

	}
	if (stuffs->watermap[e][w].N_elev < stuffs->watermap[e][w].E_elev)
	{
		stuffs->watermap[e][w].N_elev +=
			(stuffs->watermap[e][w].E_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'E', .y = 'N'}, stuffs->watermap[e][w].E_elev));
		if ((stuffs->watermap[e][w].N_elev > stuffs->watermap[e][w].E_elev))
			stuffs->watermap[e][w].N_elev = stuffs->watermap[e][w].E_elev;
	}
	if (stuffs->watermap[e][w].N_elev < stuffs->watermap[e][w].W_elev)
	{
		stuffs->watermap[e][w].N_elev +=
			(stuffs->watermap[e][w].W_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'W', .y = 'N'}, stuffs->watermap[e][w].W_elev));
		if ((stuffs->watermap[e][w].N_elev > stuffs->watermap[e][w].W_elev))
			stuffs->watermap[e][w].N_elev = stuffs->watermap[e][w].W_elev;
	}
}

void    gen_watermap(t_stuffs *stuffs, char mode)
{
	int		e;
	int		w;
	float	oldelev;
	float	temp;

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
