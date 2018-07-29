/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:17:00 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 10:20:23 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*acquire_colors(char **fields, int nbfields)
{
	int i;
	int *ret;

	ret = (int*)pr_malloc(sizeof(int) * nbfields + 1);
	i = 0;
	while (fields[i])
	{
		ret[i] = parse_color(fields[i]);
		i++;
	}
	return (ret);
}

void	free_fields(char **fields, void *to_free)
{
	int i;

	i = 0;
	while (fields[i])
	{
		free(fields[i]);
		i++;
	}
	free(fields);
	free(to_free);
}

void	set_hascol(t_stuffs *stu, int has)
{
	stu->hascolors = has;
	stu->ogcolors = stu->hascolors;
}

int		initialize(int *linenb, int *j)
{
	*linenb = 1;
	*j = 0;
	return (0);
}
