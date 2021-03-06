/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 08:07:55 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 08:10:12 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	init_line_stuffs(t_li *li, t_p2d p1, t_p2d p2)
{
	li->dx = abs(p2.x - p1.x);
	li->sx = p1.x < p2.x ? 1 : -1;
	li->dy = abs(p2.y - p1.y);
	li->sy = p1.y < p2.y ? 1 : -1;
	li->err = (li->dx > li->dy ? li->dx : -li->dy) / 2;
}

void	next_pt_line(t_li *li, t_p2d *p1)
{
	li->e2 = li->err;
	if (li->e2 > -li->dx)
	{
		li->err -= li->dy;
		p1->x += li->sx;
	}
	if (li->e2 < li->dy)
	{
		li->err += li->dx;
		p1->y += li->sy;
	}
}
