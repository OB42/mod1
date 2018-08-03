/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"
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
			s->bigmap[j][z++] = (t_p2d){.x = 0, .y = 0, .elev = 0};
		j++;
	}
}

void		fill_bigmap(t_stuffs *s, t_coords co, float whereami,t_p2d pt)
{
	int a;
	int b;

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

void		f_fill_bigmap(t_stuffs *s, t_coords co, float whereami, t_p2d pt)
{
	int a;
	int b;

	if (co.x1 == co.x2)
	{
		a = co.x1;
		b = co.y1 + whereami * s->linelen;
	}
	else
	{
		b = co.y1;
		a = co.x1 + whereami * s->linelen;
	}
	if (s->bigmap[a][b].x == 0)
		s->bigmap[a][b] = pt;
}
