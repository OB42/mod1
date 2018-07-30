/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_by_altitude.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:47:28 by obenazzo          #+#    #+#             */
/*   Updated: 2018/07/30 12:47:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int		get_color_by_altitude(int n, float max)
{
	static int colors[7] = {
		0x33cc33,
		0x009933,
		0xcccc00,
		0xcc9900,
		0x996600,
		0xe6e6e6,
		0xffffff
	};

	return (colors[n <= 0 ? 0 : (int)floor(n / max * 6.99)]);
}

float		get_max_elev(t_stuffs *stuffs)
{
	int		max;

	max = -2147483648;
	for (int x = 0; x < (stuffs->size_x * stuffs->linelen); x++)
	{
		for (int y = 0; y < (stuffs->size_x * stuffs->linelen); y++)
		{
				if (stuffs->bigmap[x][y].elev > max)
					max = stuffs->bigmap[x][y].elev;
		}
	}
	return (max);
}
