/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:31:34 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 10:31:36 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_color(int r, int g, int b)
{
	int	result;

	result = 0;
	result += r << 16;
	result += g << 8;
	result += b;
	return (result);
}

t_rgb	int_to_rgb(int col)
{
	t_rgb result;

	result.blue = col & 255;
	result.green = (col >> 8) & 255;
	result.red = (col >> 16) & 255;
	return (result);
}

int		rgb_to_int(t_rgb col)
{
	int	result;

	result = 0;
	result += col.red << 16;
	result += col.green << 8;
	result += col.blue;
	return (result);
}
