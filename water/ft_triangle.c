/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

char	point_in_triangle(t_p2d s, t_p2d a, t_p2d b, t_p2d c)
{
	int		as_x;
	int		as_y;
	char	s_ab;

	as_x = s.x - a.x;
	as_y = s.y - a.y;
	s_ab = (b.x - a.x) * as_y - (b.y - a.y) * as_x > 0;
	if (((c.x - a.x) * as_y - (c.y - a.y) * as_x > 0 == s_ab)
	|| ((c.x - b.x) * (s.y - b.y) - (c.y - b.y) * (s.x - b.x) > 0 != s_ab))
		return (0);
	return (1);
}

void	ft_triangle(t_stuffs *s, int e, int w)
{
	t_p2d	tmp_a;
	t_p2d	tmp_b;
	t_p2d	tmp_c;
	int		l;
	int		h;

	l = s->linelen;
	tmp_a = (t_p2d){.x = (e - (e % l)), .y = (w - (w % l))};
	tmp_b = (t_p2d){.x = (e - (e % l)), .y = (w + (l - (w % l)))};
	tmp_c = (t_p2d){.x = (e - (e % l) + (l / 2)), .y = (w - (w % l) + (l / 2))};
	h = s->water->bigmap[e][w].elev;
	if (point_in_triangle((t_p2d){.x = e, .y = w}, tmp_a,
				(t_p2d){.x = (e + (l - (e % l))), .y = (w - (w % l))}, tmp_c))
		h = s->watermap[(e / l) + 1][(w / l) + 1].n_elev - s->bigmap[e][w].elev;
	else if (point_in_triangle((t_p2d){.x = e, .y = w}, tmp_b,
				(t_p2d){.x = e + (l - (e % l)), .y = w + (l - (w % l))}, tmp_c))
		h = s->watermap[(e / l) + 1][(w / l) + 1].s_elev - s->bigmap[e][w].elev;
	else if (point_in_triangle((t_p2d){.x = e, .y = w}, tmp_a, tmp_b, tmp_c))
		h = s->watermap[(e / l) + 1][(w / l) + 1].e_elev - s->bigmap[e][w].elev;
	else if (point_in_triangle((t_p2d){.x = e, .y = w},
				(t_p2d){.x = e + (l - (e % l)), .y = (w - (w % l))},
				(t_p2d){.x = e + (l - (e % l)), .y = w + (l - (w % l))}, tmp_c))
		h = s->watermap[(e / l) + 1][(w / l) + 1].w_elev - s->bigmap[e][w].elev;
	s->water->bigmap[e][w].elev = h;
}
