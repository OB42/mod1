/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:12:01 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 10:15:37 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				nb_fields(char **fields)
{
	int i;

	i = 0;
	while (fields[i])
	{
		i++;
	}
	return (i);
}

int				*acquire_elev(char **fields, int nbfields, int water)
{
	int i;
	int *ret;

	ret = (int*)pr_malloc(sizeof(int) * (nbfields + 1));
	i = 0;
	while (fields[i])
	{
		ret[i] = water ? (35) : ft_atoi(fields[i]);
		i++;
	}
	return (ret);
}

unsigned char	twochar_to_byte(char a, char b)
{
	unsigned char ret;

	ret = 0;
	a = ft_tolower(a);
	b = ft_tolower(b);
	if (ft_isdigit(a))
		ret += (a - '0') * 16;
	else
		ret += (a - 'a' + 10) * 16;
	if (ft_isdigit(b))
		ret += (b - '0');
	else
		ret += (b - 'a' + 10);
	return (ret);
}

int				parse_color(char *field)
{
	int				i;
	int				to;
	int				color;
	unsigned char	byte;
	int				cpt;

	if (!ft_is_in(',', field))
		return (0xFFFFFF);
	i = 0;
	while (field[i] && (field[i] != 'x'))
		i++;
	to = i++;
	while (ft_is_in(field[i], "0123456789abcdefABCDEF"))
		i++;
	i--;
	cpt = 0;
	color = 0;
	while (i > to && cpt < 3)
	{
		byte = twochar_to_byte(field[i - 1], field[i]);
		color += (byte << (cpt * 8));
		i -= 2;
		cpt++;
	}
	return (color);
}

char			has_color(char **fields, int nbfields)
{
	int i;

	nbfields++;
	i = 0;
	while (fields[i])
	{
		if (ft_is_in(',', fields[i]))
			return (1);
		i++;
	}
	return (0);
}
