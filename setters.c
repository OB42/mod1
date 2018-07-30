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

#include "fdf.h"

void	set_props(t_stuffs *stu)
{
	float len;
	float leny;
	float leny2;
	float lenx;

	len =  (float)stu->size_y * 3;
	leny =  (float)stu->size_y * 1.5;
	leny2 =  (float)stu->size_x * 1.5;
	lenx =  (float)stu->size_x * 3;
	len = (len < lenx) ? len : lenx;
	leny2 = (leny < leny2) ? leny : leny2;
	stu->props = (t_f2d){.x = len, .y = leny2};
}

void	malloc_map(t_stuffs *stu)
{
	int i;

	stu->map = (t_p2d**)pr_malloc(sizeof(t_p2d*) * stu->size_x + 1);
	i = 0;
	while (i <= stu->size_x)
	{
		stu->map[i] = (t_p2d*)pr_malloc(sizeof(t_p2d) * stu->size_y + 1);
		i++;
	}
}

void	altinfos_set(t_stuffs *stu, int r)
{
	if (r < stu->altinfos.y)
		stu->altinfos.y = r;
	if (r > stu->altinfos.x)
		stu->altinfos.x = r;
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
	if (abs(vals.y) > abs(vals.x))
		inval = abs(vals.y);
	else
		inval = abs(vals.x);
	if (inval && inval > 120)
		stuffs->coef = 130 / (float)inval;
	else
		stuffs->coef = 1;
}
