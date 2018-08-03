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
		free(fields[i++]);
	free(fields);
	free(to_free);
}

int		initialize(int *linenb, int *gnl, char *filename, int *fd)
{
	*linenb = 1;
	*gnl = 1;
	*fd = open(filename, O_RDONLY);
	return (0);
}
