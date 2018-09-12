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

void	init_watermap(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 1;
	while (e <= stuffs->size_x)
	{
		w = 1;
		while (w <= stuffs->size_y)
		{
			stuffs->watermap[e][w].N_elev = 0;
			stuffs->watermap[e][w].W_elev = 0;
			stuffs->watermap[e][w].E_elev = 0;
			stuffs->watermap[e][w].S_elev = 0;
			stuffs->watermap[e][w].x = 0;
			stuffs->watermap[e][w].y = 0;
			w++;
		}
		e++;
	}
}

void	malloc_watermap(t_stuffs *stu)
{
	int i;

	stu->watermap = (t_4triangles**)pr_malloc(sizeof(t_4triangles*)
														* (stu->size_x + 1));
	i = 0;
	while (i <= stu->size_x)
		stu->watermap[i++] = (t_4triangles*)pr_malloc(sizeof(t_4triangles)
														* (stu->size_y + 1));
	init_watermap(stu);
}
