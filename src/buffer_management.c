/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 01:01:05 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/11 01:07:57 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	malloc_buffer(int x, int y, t_stuffs *stu)
{
	int i;
	int j;

	stu->buffer = (char**)(pr_malloc(sizeof(char*) * x + 1));
	i = 0;
	while (i < x)
		stu->buffer[i++] = (char*)(pr_malloc(sizeof(char) * y + 1));
}

void	init_buffer(int x, int y, t_stuffs *stu)
{
	int i;
	int j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
			stu->buffer[i][j++] = 0;
		i++;
	}
}
