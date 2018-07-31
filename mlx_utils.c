/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_pixel(int x, int y, int color, t_stuffs *stuffs)
{
	if (x < WINX && y < WINY && y >= 0 && x >= 0)
		*(int *)(stuffs->img.img_addr + ((int)(y * WINX + x) * 4)) = color;
}

void	clear(t_stuffs *stuffs)
{
	ft_memset(stuffs->img.img_addr, 0, stuffs->img.line_size * WINY);
}
