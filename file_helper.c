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

#include "mod1.h"

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

int		initialize(int *linenb, int *gnl, char *filename, int *fd)
{
	*linenb = 1;
	*gnl = 1;
	*fd = open(filename, O_RDONLY);
	return (0);
}
