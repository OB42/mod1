/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"
#include <math.h>
#include <unistd.h>

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

void		malloc_bigmap(t_stuffs *s)
{
	int j;
	int z;

	s->bigmap = pr_malloc(sizeof(t_p2d*) * (s->size_x * s->linelen + 1));
	j = 0;
	while (j < (s->size_x * s->linelen))
	{
		s->bigmap[j] = pr_malloc(sizeof(t_p2d) * (s->size_y * s->linelen + 1));
		z = 0;
		while (z < s->size_y * s->linelen)
			s->bigmap[j][z++] = (t_p2d){.x = 0, .y = 0, .elev = 0, .color = 0};
		j++;
	}
}

void             line(t_p2d p1, t_p2d p2, t_stuffs *s, int color)
{
	t_li    val;
	static	unsigned	int rain = 1;
	init_line_stuffs(&val, p1, p2);
	while (1)
	{
		if (s->raining && !p1.is_water && ((p1.elev + rain) % 2 && p1.x % 4 == rain % 4) && p1.elev)
		{
			//printing droplets on the hills
			set_pixel(s->img.x + p1.x, s->img.y + p1.y, 0x00ccff, s);
		}
		else
			set_pixel(s->img.x + p1.x, s->img.y + p1.y, color, s);
		rain += 1;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
}

void		fill_bigmap(t_stuffs *s, t_coords co, float whereami,t_p2d pt)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (co.x1 == co.x2)
	{
		a = (co.x1 - 1) * s->linelen;
		b = ((co.y1 - 1) * s->linelen) + whereami * s->linelen;
	}
	else
	{
		b = (co.y1 - 1) * s->linelen;
		a = ((co.x1 - 1) * s->linelen) + whereami * s->linelen;
	}
	s->bigmap[a][b] = pt;
}

t_p2d		gen_point(t_p2d p1, t_p2d p2, float whereami)
{
	float coef;
	float sinuscorrect;
	int elevnow;
	float sinelev;
	t_p2d ret;

	coef = whereami;
	sinuscorrect = -(M_PI/2.0);
	elevnow = ((float)p2.elev - (float)p1.elev);
	if (p2.elev < p1.elev)
	{
		elevnow = ((float)p1.elev - (float)p2.elev);
		coef = 1.0 - whereami;
		sinuscorrect = M_PI/2.0;
	}
	sinelev =  sin(whereami * M_PI +  sinuscorrect)+1.0;

	ret = p1;
	ret.y -=  fabs(sinelev/2.0 * ((float)elevnow));
	if (p1.elev != 0 &&  p2.elev != 0)
	{
		if (p2.elev > p1.elev)
			ret.y -=  abs(p1.elev) ;
		else
			ret.y -=  abs(p2.elev) ;
	}
	ret.elev =  abs(p1.y - ret.y);
	return (ret);
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

void		f_fill_bigmap(t_stuffs *s, t_coords co, float whereami,t_p2d pt)
{
	int a;
	int b;

	a = 0;
	b = 0;

	if (co.x1 == co.x2)
	{
		a = (co.x1 ) ;
		b = ((co.y1 ) ) + whereami * s->linelen;
	}
	else
	{
		b = (co.y1 ) ;
		a = ((co.x1 ) ) + whereami * s->linelen;
	}
	if (s->bigmap[a][b].x ==0)
	{
		s->bigmap[a][b] = pt;
		s->bigmap[a][b].color = -1;
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
