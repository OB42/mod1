/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:54:56 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/15 05:54:58 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	set_props(t_stuffs *stu)
{
	float len;
	float leny;
	float leny2;
	float lenx;

	len = 391 / (float)stu->size_y;
	leny = 220 / (float)stu->size_y;
	leny2 = 220 / (float)stu->size_x;
	lenx = 391 / (float)stu->size_x;
	len = (len < lenx) ? len : lenx;
	leny2 = (leny < leny2) ? leny : leny2;
	stu->props = (t_f2d){.x = len, .y = leny2};
}

void	malloc_map(t_stuffs *stu)
{
	int i;

	stu->map = (t_p2d**)pr_malloc(sizeof(t_p2d*) * (stu->size_x + 1));
	i = 0;
	while (i <= stu->size_x)
		stu->map[i++] = (t_p2d*)pr_malloc(sizeof(t_p2d) * (stu->size_y + 1));
}

t_p2d	get_elevlimits(t_stuffs *stuffs)
{
	int		i;
	int		j;
	t_p2d	ret;

	ret.x = INT_MIN;
	ret.y = INT_MAX;
	i = 1;
	while (i <= stuffs->size_x)
	{
		j = 1;
		while (j <= stuffs->size_y)
		{
			if (ret.x < stuffs->elevs[i][j])
				ret.x = stuffs->elevs[i][j];
			if (ret.y > stuffs->elevs[i][j])
				ret.y = stuffs->elevs[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}

void	set_scale(t_stuffs *stuffs)
{
	t_p2d	vals;
	int		inval;

	vals = get_elevlimits(stuffs);
	inval = (abs(vals.y) > abs(vals.x)) ? abs(vals.y) : abs(vals.x);
	stuffs->coef = 1;//(inval > 120) ? (130 / (float)inval) : 1;
}
