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

#include "fdf.h"

void	malloc_buffer(int x, int y, t_stuffs *stu)
{
	int i;
	int j;

	stu->buffer = (char**)(malloc(sizeof(char*) * x + 1));
	i = 0;
	while (i < x)
	{
		stu->buffer[i] = (char*)(malloc(sizeof(char) * y + 1));
		i++;
	}
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
		{
			stu->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	add_pt_buffer(t_stuffs *stu, t_p2d pt)
{
	stu->buffer[pt.x][pt.y] = 1;
}
