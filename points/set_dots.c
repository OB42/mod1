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

#include "mod1.h"

void	detailed_point(t_stuffs *s, int ie, int je, t_f2d noww)
{
	int		r;
	t_f2d	temp;
	int		col;

	col = 0xFFFFFF;
	r = (float)(s->elevs)[ie][je] * s->coef;
	temp = (t_f2d){.x = noww.x + s->props.x * je,
		.y = (noww.y + s->props.y * je) - r, .elev = r};
	je++;
	s->map[ie][je - 1] = f2d_to_p2d(temp);
}

void	set_dec(t_stuffs *s, t_p2d *p1)
{
	int		nb[2];
	t_f2d	noww;
	t_f2d	temp;
	int		min;

	p1->elev = 1;
	nb[0] = 1;
	min = 0;
	while (nb[0] <= s->size_x)
	{
		nb[1] = 1;
		noww = (t_f2d){.x = p1->x - (s->props.x * nb[0]),
			.y = (p1->y + s->props.y * nb[0]), .elev = 0 };
		temp = (t_f2d){.x = noww.x, .y = noww.y - s->coef *
			(float)(s->elevs)[nb[0]][nb[1]], .elev =
			(float)(s->elevs)[nb[0]][nb[1]] * s->coef};
		if (f2d_to_p2d(temp).x < min)
			min = f2d_to_p2d(temp).x;
		nb[0]++;
	}
	p1->x -= min;
}

void	set_dots(t_stuffs *s)
{
	int				r;
	static t_p2d	p1 = {.elev = -1, .y = 100, .x = 400};
	int				nb[2];
	t_f2d			noww;
	t_f2d			temp;

	if (p1.elev == -1)
		set_dec(s, &p1);
	nb[0] = 1;
	ft_printf("Calculating dots...\n");
	while (nb[0] <= s->size_x)
	{
		nb[1] = 1;
		r = (float)(s->elevs)[nb[0]][nb[1]] * s->coef;
		noww = (t_f2d){.x = p1.x - (s->props.x * nb[0]),
			.y = (p1.y + s->props.y * nb[0]), .elev = 0 };
		temp = (t_f2d){.x = noww.x, .y = noww.y - r, .elev = r};
		s->map[nb[0]][nb[1]] = f2d_to_p2d(temp);
		while (nb[1] <= s->size_y)
			detailed_point(s, nb[0], nb[1]++, noww);
		nb[0]++;
	}
}
