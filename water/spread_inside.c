/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_watermap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2018/09/12 16:05:36 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

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
	t_p2d coo;
	t_p2d where;
	float	*elv;
	float	*elv2;

	coo.y = 'E';
	where = (t_p2d){.x = e, .y = w}; 
	elv = &(stuffs->watermap[e][w].E_elev);
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

void	inside_north(t_stuffs *stuffs , int e, int w)
{
	t_p2d coo;
	t_p2d where;
	float	*elv;
	float	*elv2;

	coo.y = 'N';
	where = (t_p2d){.x = e, .y = w}; 
	elv = &(stuffs->watermap[e][w].N_elev);
	if (*(elv) < stuffs->watermap[e][w].E_elev)
	{
		elv2 = &(stuffs->watermap[e][w].E_elev);
		coo.x = 'E';
		*(elv) += (*(elv2) * coef_inside(stuffs, where, coo, *(elv2)));
		if (*(elv) > stuffs->watermap[e][w].E_elev)
			*(elv) = stuffs->watermap[e][w].E_elev;
	}
	if (*(elv) < stuffs->watermap[e][w].W_elev)
	{
		elv2 = &(stuffs->watermap[e][w].W_elev);
		coo.x = 'W';
		*(elv) += (*(elv2) * coef_inside(stuffs, where, coo, *(elv2)));
		if (*(elv) > stuffs->watermap[e][w].W_elev)
			*(elv) = stuffs->watermap[e][w].W_elev;
	}
}

void	inside_south(t_stuffs *stuffs, int e, int w)
{
	t_p2d coo;
	t_p2d where;
	float	*elv;
	float	*elv2;

	coo.y = 'S';
	where = (t_p2d){.x = e, .y = w}; 
	elv = &(stuffs->watermap[e][w].S_elev);
	if (*(elv) < stuffs->watermap[e][w].E_elev)
	{
		elv2 = &(stuffs->watermap[e][w].E_elev);
		coo.x = 'E';
		*(elv) += (*(elv2) * coef_inside(stuffs, where, coo, *(elv2)));
		if (*(elv) > stuffs->watermap[e][w].E_elev)
			*(elv) = stuffs->watermap[e][w].E_elev;
	}
	if (*(elv) < stuffs->watermap[e][w].W_elev)
	{
		elv2 = &(stuffs->watermap[e][w].W_elev);
		coo.x = 'W';
		*(elv) += (*(elv2) * coef_inside(stuffs, where, coo, *(elv2)));
		if (*(elv) > stuffs->watermap[e][w].W_elev)
			*(elv) = stuffs->watermap[e][w].W_elev;
	}
}

void	water_inside(t_stuffs *stuffs, int e, int w)
{
	inside_west(stuffs, e, w);
	inside_south(stuffs, e, w);
	inside_east(stuffs, e, w);
	inside_north(stuffs, e, w);
}
