/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_feed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 04:12:54 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 11:04:22 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				file_test(char *filename, t_stuffs *stu)
{
	char	*line;
	char	**fields;
	int		linenb;
	int		j;
	int		fd;

	errno = initialize(&linenb, &j);
	if (!ft_printf("File Check...\n") || (fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &line))
	{
		if (errno)
			return (-2);
		fields = ft_strsplit(line, ' ');
		if (linenb == 1)
			stu->size_y = nb_fields(fields);
		else if (stu->size_y != nb_fields(fields))
			return (linenb);
		if (!(linenb++) || !((stu->size_x = linenb - 1) + 1) || !stu->hascolors)
			set_hascol(stu, has_color(fields, stu->size_y));
		free_fields(fields, line);
	}
	free(line);
	close(fd);
	return (0);
}

void			malloc_ec(t_stuffs *stu)
{
	int i;

	ft_printf("Parsing file...\n");
	stu->elevs = (int**)malloc(stu->size_x * sizeof(int*) + 1);
	if (stu->hascolors)
		(stu->colors) = (int**)malloc(stu->size_x * sizeof(int*) + 1);
	i = 1;
	while (i <= stu->size_x + 1)
	{
		if (stu->hascolors)
			(stu->colors)[i] = (int*)malloc(stu->size_y * sizeof(int) + 1);
		(stu->elevs)[i] = (int*)malloc(stu->size_y * sizeof(int) + 1);
		i++;
	}
}

void			fill_ec(t_stuffs *stu, int **colors, int **elevs, int id)
{
	int i;

	i = 0;
	while (i <= stu->size_y)
	{
		(stu->hascolors) ? (stu->colors)[id][i + 1] = (*colors)[i] : 0;
		(stu->elevs)[id][i + 1] = (*elevs)[i];
		i++;
	}
}

int				file_feed(char *filename, t_stuffs *stu)
{
	char	*line;
	char	**fields;
	int		*elevs;
	int		*colors;
	int		i[4];

	i[0] = open(filename, O_RDONLY);
	if ((i[1] = file_test(filename, stu)))
		return (i[1]);
	malloc_ec(stu);
	i[3] = 1;
	while (get_next_line(i[0], &line))
	{
		fields = ft_strsplit(line, ' ');
		elevs = acquire_elev(fields, stu->size_y);
		(stu->hascolors) ? colors = acquire_colors(fields, stu->size_y) : 0;
		fill_ec(stu, &colors, &elevs, i[3]);
		free_fields(fields, line);
		free(elevs);
		free(colors);
		i[3]++;
	}
	free(line);
	close(i[0]);
	return (i[1]);
}
