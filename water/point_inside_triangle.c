/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_inside_triangle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

char	point_inside_triangle(t_p2d s, t_p2d a, t_p2d b, t_p2d c)
{
	int		as_x;
	int		as_y;
	char	s_ab;

	as_x = s.x - a.x;
	as_y = s.y - a.y;
	s_ab = (b.x - a.x) * as_y - (b.y - a.y) * as_x > 0;
	if (((c.x - a.x) * as_y - (c.y - a.y) * as_x > 0 == s_ab)
	|| ((c.x - b.x) * (s.y - b.y) - (c.y - b.y) * (s.x - b.x) > 0 != s_ab))
		return 0;
	return 1;
}
