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

#include "fdf.h"
#include <math.h>
#include <unistd.h>

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

	init_line_stuffs(&val, p1, p2);
	while (1)
	{
		set_pixel(s->img.x + p1.x, s->img.y + p1.y, color, s);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
}

void             special_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co)
{
	t_li    val;
	int             line_len;
	int cpt;
	int color;
	t_p2d   fto;
	t_p2d   prevpoint;
	t_p2d   prevcoords;

	p1.y += p1.elev;
	p2.y += p2.elev;
	init_line_stuffs(&val, p1, p2);
	line_len = line_count(p1,p2);

	if (s->linelen == -1)
	{
		s->linelen = line_len;
		malloc_bigmap(s);
	}
	cpt = 0;
	t_p2d dpoint;
	fto = set_fromto(s, p1, p2);
	while (1)
	{
		float whereami = ((float)cpt/(float)line_len);

		float coef = whereami;
		float sinuscorrect = -(M_PI/2.0);
		int elevnow = ((float)p2.elev - (float)p1.elev);
		if (p2.elev < p1.elev)
		{
			elevnow = ((float)p1.elev - (float)p2.elev);
			coef = 1.0 - whereami;
			sinuscorrect = M_PI/2.0;
		}
		float sinelev =  sin(whereami * M_PI +  sinuscorrect)+1.0;

		dpoint = p1;
		dpoint.y -=  fabs(sinelev/2.0 * ((float)elevnow));
		if (p1.elev != 0 &&  p2.elev != 0)
		{

			if (p2.elev > p1.elev)
				dpoint.y -=  abs(p1.elev) ;
			else
				dpoint.y -=  abs(p2.elev) ;
		}
		int a;
		int b;

		a = 0;
		b = 0;
		//bigmap setting:
		//int posinow = whereami * (float)line_len;
		if (1)
		{
			prevcoords = (t_p2d){.x = a, .y = b};
			if (co.x1 == co.x2)
			{
				a = (co.x1 - 1) * line_len;
				b = ((co.y1 - 1) * line_len) + whereami * s->linelen;
			}
			else
			{
				b = (co.y1 - 1) * line_len;
				a = ((co.x1 - 1) * line_len) + whereami * s->linelen;
			}
			s->bigmap[a][b] = dpoint;
			s->bigmap[a][b].elev = p1.y - dpoint.y ;//abs(dpoint.y - p1.y);
		}
		float red = fto.y + ((fto.x - fto.y)) * whereami;
		color = get_color(0, red, 128 - (red/2));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		prevpoint = p1;
		next_pt_line(&val, &p1);
		cpt++;
	}
}

void             special_fine_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co)
{
	t_li    val;
	int             line_len;
	int cpt;
	int color;
	t_p2d   fto;

	p1.y += p1.elev;
	p2.y += p2.elev;
	init_line_stuffs(&val, p1, p2);
	line_len = line_count(p1,p2);
	cpt = 0;
	t_p2d dpoint;
	fto = set_fromto(s, p1, p2);
	while (1)
	{
		float whereami = ((float)cpt/(float)line_len);
		float coef = whereami;
		float sinuscorrect = -(M_PI/2.0);
		int elevnow = ((float)p2.elev - (float)p1.elev);
		if (p2.elev < p1.elev)
		{
			elevnow = ((float)p1.elev - (float)p2.elev);
			coef = 1 - whereami;
			sinuscorrect = (M_PI/2.0);
		}
		float sinelev = sin(whereami * M_PI +  sinuscorrect)+1;
		dpoint = p1;
		dpoint.y -= fabs(sinelev * (elevnow/2));
		if (p1.elev != 0 &&  p2.elev != 0)
		{
			if (p2.elev > p1.elev)
				dpoint.y -=  abs(p1.elev) ;
			else
				dpoint.y -=  abs(p2.elev) ;
		}

		float red = fto.y + ((fto.x - fto.y)) * whereami;
		int a;
		int b;
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
			s->bigmap[a][b] = dpoint;
			s->bigmap[a][b].elev = abs(dpoint.y - p1.y);
			s->bigmap[a][b].color = -1;
		}
		color = get_color(0, red, 128 - (red/2));

		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
		cpt++;
	}
}
