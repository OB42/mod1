/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	detailed_point(t_stuffs *s, int ie, int je, t_f2d noww)
{
	int		r;
	t_f2d	temp;
	int		col;

	col = 0xFFFFFF;
	r = (float)(s->elevs)[gorx(s, ie)][gory(s, je)] * s->coef;
	if (s->hascolors)
		col = (s->colors)[gorx(s, ie)][gory(s, je)];
	altinfos_set(s, r);
	temp = (t_f2d){.x = noww.x + s->props.x * je,
		.y = (noww.y + s->props.y * je) - r, .elev = r};
	temp.color = col;
	je++;
	s->map[ie][je - 1] = f2d_to_p2d(temp);
}

void	set_dots(t_stuffs *s)
{
	int		r;
	t_p2d	p1;
	int		nb[3];
	t_f2d	noww;
	t_f2d	temp;

	p1 = (t_p2d){.x = 400, .y = 100, .color = 0xFF00FF };
	nb[0] = 1;
	ft_printf("Calculating dots...\n");
	while (nb[0] <= s->size_x)
	{
		nb[1] = 1;
		r = (float)(s->elevs)[gorx(s, nb[0])][gory(s, nb[1])] * s->coef;
		if (s->hascolors)
			nb[2] = (s->colors)[gorx(s, nb[0])][gory(s, nb[1])];
		altinfos_set(s, r);
		noww = (t_f2d){.x = p1.x - (s->props.x * nb[0]),
			.y = (p1.y + s->props.y * nb[0]), .elev = 0 };
		temp = (t_f2d){.x = noww.x, .y = noww.y - r, .elev = r};
		temp.color = nb[2];
		s->map[nb[0]][nb[1]] = f2d_to_p2d(temp);
		while (nb[1] <= s->size_y)
			detailed_point(s, nb[0], nb[1]++, noww);
		nb[0]++;
	}
}
