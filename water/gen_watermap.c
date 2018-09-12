/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_watermap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2018/09/12 15:51:29 by pcluchet         ###   ########.fr       */
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
			stuffs->watermap[e][1].N_elev +=  0.15;
			stuffs->watermap[e][stuffs->size_y - 1].S_elev +=  0.15;
		}
		else
			stuffs->watermap[e][1].N_elev +=  0.8;
		w = 1;
		while (w <= stuffs->size_y && mode == 'R')
		{
			stuffs->watermap[1][w].E_elev +=  0.15;
			stuffs->watermap[stuffs->size_x - 1][w].E_elev +=  0.15;
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

void	between_vertical (t_stuffs *stuffs, int e, int w, char dir)
{
	int cc;
	float *c1;
	float *c2;
	t_p2d coo;

	cc = 0;
	coo = (t_p2d){.x = e, .y = w}; 
	if (dir == 'S')
	{
		cc = 1;
		c1 = &(stuffs->watermap[e][w + cc].N_elev);
		c2 = &(stuffs->watermap[e][w].S_elev);
	}
	if (dir == 'N')
	{
		cc = -1;
		c1 = &(stuffs->watermap[e][w + cc].S_elev);
		c2 = &(stuffs->watermap[e][w].N_elev);
	}
		*(c1) += *(c2) * coef_between(stuffs, coo, dir, *(c2));
		if (*(c1) > *(c2))
			*(c1) = *(c2);
}

void	between_horiz (t_stuffs *stuffs, int e, int w, char dir)
{
	int cc;
	float *c1;
	float *c2;
	t_p2d coo;

	cc = 0;
	coo = (t_p2d){.x = e, .y = w}; 
	if (dir == 'W')
	{
		cc = 1;
		c1 = &(stuffs->watermap[e + cc][w].E_elev);
		c2 = &(stuffs->watermap[e][w].W_elev);
	}
	if (dir == 'E')
	{
		cc = -1;
		c1 = &(stuffs->watermap[e + cc][w].W_elev);
		c2 = &(stuffs->watermap[e][w].E_elev);
	}
		*(c1) += *(c2) * coef_between(stuffs, coo, dir, *(c2));
		if (*(c1) > *(c2))
			*(c1) = *(c2);
}

void	water_between (t_stuffs *stuffs, int e, int w)
{
	t_cardinals cars;

	cars = to_calc_between(stuffs, e, w);
	if (cars.s)
		between_vertical (stuffs, e, w, 'S');
	if (cars.n)
		between_vertical (stuffs, e, w, 'N');
	if (cars.w)
		between_horiz (stuffs, e, w, 'W');
	if (cars.e)
		between_horiz (stuffs, e, w, 'E');
}

void	inside_west(t_stuffs *stuffs, int e, int w)
{
	t_p2d coo;
	t_p2d where;
	float	*elv;
	float	*elv2;

	coo.y = 'W';
	where = (t_p2d){.x = e, .y = w}; 
	elv = &(stuffs->watermap[e][w].W_elev);
	if (*(elv) < stuffs->watermap[e][w].N_elev)
	{
		elv2 = &(stuffs->watermap[e][w].N_elev);
		coo.x = 'N';
		*(elv) += (*(elv2) * coef_inside(stuffs, where, coo, *(elv2)));
		if (*(elv) > stuffs->watermap[e][w].N_elev)
			*(elv) = stuffs->watermap[e][w].N_elev;
	}
	if (*(elv) < stuffs->watermap[e][w].S_elev)
	{
		elv2 = &(stuffs->watermap[e][w].S_elev);
		coo.x = 'S';
		*(elv) += (*(elv2) * coef_inside(stuffs, where, coo, *(elv2)));
		if (*(elv) > stuffs->watermap[e][w].S_elev)
			*(elv) = stuffs->watermap[e][w].S_elev;
	}
}

void	inside_east(t_stuffs *stuffs, int e, int w)
{
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
}

void	inside_north(t_stuffs *stuffs , int e, int w)
{
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

void	inside_south(t_stuffs *stuffs, int e, int w)
{
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
}

void	water_inside(t_stuffs *stuffs, int e, int w)
{
	inside_west(stuffs, e, w);
	inside_south(stuffs, e, w);
	inside_east(stuffs, e, w);
	inside_north(stuffs, e, w);
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
