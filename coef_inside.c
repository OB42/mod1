/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coef_inside.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

t_inside	get_coefs(t_p2d f)
{
	t_inside coefs;
	if ((f.x == 'N' && f.y == 'E') || (f.x == 'E' && f.y == 'N'))
		coefs = (t_inside){.fromx = 1, .fromy = 1, .loopx = 1, .loopy = 1 };
	if ((f.x == 'W' && f.y == 'N') || (f.x == 'N' && f.y == 'W'))
		coefs = (t_inside){.fromx = 0, .fromy = 1, .loopx = -1, .loopy = 1 };
	if ((f.x == 'S' && f.y == 'W') || (f.x == 'W' && f.y == 'S'))
		coefs = (t_inside){.fromx = 0, .fromy = 0, .loopx = -1, .loopy = -1 };
	if ((f.x == 'E' && f.y == 'S') || (f.x == 'S' && f.y == 'E'))
		coefs = (t_inside){.fromx = 1, .fromy = 0, .loopx = 1, .loopy = -1 };
	return (coefs);
}

float	coef_inside(t_stuffs *stuffs, t_p2d coords, t_p2d fromto, int water_lvl)
{
	t_p2d from;
	t_inside coefs;
	float cpt;
	int i;

	coefs = get_coefs(fromto);
	cpt = 0.0;
	from.x = (coords.x - coefs.fromx) * stuffs->linelen;
	from.y = (coords.y - coefs.fromy) * stuffs->linelen;
	i = 0;
	while ((i < (stuffs->linelen / 2)) &&
	(from.x + (i * coefs.loopx)) < (stuffs->size_x * stuffs->linelen) &&
	(from.y + (i * coefs.loopy)) < (stuffs->size_y * stuffs->linelen))
	{
		if (stuffs->bigmap[from.x + (i * coefs.loopx)][from.y +
		(i * coefs.loopy)].elev < water_lvl)
			cpt++;
		i++;
	}
	cpt = (((float)cpt)/ (stuffs->linelen / 2.0) - 0.0);
	cpt = (cpt > 0.5) ? 1.0 : cpt;
	return ((cpt > 0) ? cpt : 0.0);
}
