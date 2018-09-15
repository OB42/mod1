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

#include "mod1.h"

int				nb_fields(char **fields)
{
	int i;

	i = 0;
	while (fields[i])
		i++;
	return (i);
}

int				*acquire_elev(char **fields, int nbfields, int water, int side)
{
	int i;
	int *ret;

	ret = (int*)pr_malloc(sizeof(int) * (nbfields + 1));
	i = 0;
	while (fields[i])
	{
		if (ft_atoi(fields[i]) > 200 || ft_atoi(fields[i]) < 0)
		{
			ft_printf("Invalid height.(too large/too small)\n");
			exit(1);
		}
		ret[i++] = (water || nbfields == (i + 1) || side || !i) ?
		0 : ft_atoi(fields[i]);
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
