/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

int		line_count(t_p2d p1, t_p2d p2)
{
	t_li	val;
	int		ct;

	init_line_stuffs(&val, p1, p2);
	ct = 0;
	while (1)
	{
		ct++;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
	return (ct);
}


void             line(t_p2d p1, t_p2d p2, t_stuffs *s, int color)
{
	t_li    val;
	static	unsigned	int rain = 1;

	init_line_stuffs(&val, p1, p2);
	while (1)
	{
		if (s->raining && !p1.is_water && ((p1.elev + rain) % 2 && p1.x % 4 == rain % 4) && p1.elev)
			set_pixel(s->img.x + p1.x, s->img.y + p1.y, 0x00ccff, s);//printing droplets on the hills
		else
			set_pixel(s->img.x + p1.x, s->img.y + p1.y, color, s);
		rain++;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
}

void             special_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co)
{
	t_li    val;
	int cpt;
	float whereami;

	p1.y += p1.elev;
	p2.y += p2.elev;
	init_line_stuffs(&val, p1, p2);
	if (s->linelen == -1)
	{
		s->linelen = line_count(p1,p2);
		malloc_bigmap(s);
	}
	cpt = 0;
	while (1)
	{
		whereami = ((float)cpt/(float)s->linelen);
		fill_bigmap(s, co, whereami, gen_point(p1, p2, whereami));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
		cpt++;
	}
}

void             special_fine_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co)
{
	t_li    val;
	int cpt;
	float whereami;
	t_p2d dpoint;

	p1.y += p1.elev;
	p2.y += p2.elev;
	init_line_stuffs(&val, p1, p2);
	cpt = 0;
	while (1)
	{
		whereami = ((float)cpt/(float)s->linelen);
		dpoint =  gen_point(p1, p2, whereami);
		f_fill_bigmap(s, co, whereami, dpoint);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
		cpt++;
	}
}
