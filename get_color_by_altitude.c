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
	static int colors[20] = {
		0x04AF17,
		0x16A614,
		0x3C9610,
		0x61860B,
		0x747E09,
		0x867606,
		0x996E04,
		0xAC6602,
		0xBF5E00,
		0xC56E19,
		0xCB7E33,
		0xD28E4C,
		0xD89E66,
		0xDFAE7F,
		0xE5BE99,
		0xEBCEB2,
		0xF2DECC,
		0xF8EEE5,
		0xFFFFEE,
		0xFFFFFF
	};

	if (n < 100)
		return (colors[n <= 0 ? 0 : (int)floor(n / 5)]);
	return (colors[19]);
}
