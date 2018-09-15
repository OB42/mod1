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

#include "mod1.h"

int				file_test(char *filename, t_stuffs *stu)
{
	char	*line;
	char	**fields;
	int		linenb;
	int		gnl;
	int		fd;

	errno = initialize(&linenb, &gnl, filename, &fd);
	if (fd == -1)
		return (-1);
	while ((gnl == get_next_line(fd, &line)) == 1)
	{
		if (errno)
			return (-2);
		fields = ft_strsplit(line, ' ');
		stu->size_y = (linenb == 1) ? nb_fields(fields) : stu->size_y;
		if (stu->size_y != nb_fields(fields))
			return (linenb);
		stu->size_x = linenb++;
		free_fields(fields, line, 0);
	}
	if (gnl == -1)
		print_error("gnl error\n");
	free(line);
	close(fd);
	return (0);
}


void			fill_ec(t_stuffs *stu, int **elevs, int id)
{
	int i;

	i = 0;
	while (i < stu->size_y)
	{
		(stu->elevs)[id][i + 1] = (*elevs)[i];
		i++;
	}
}

int				file_feed(char *filename, t_stuffs *stu)
{
	char	*line;
	char	**fields;
	int		*elevs;
	int		i[6];

	i[0] = open(filename, O_RDONLY);
	if (i[0] == -1 || (i[1] = file_test(filename, stu)))
		return (-1);
	malloc_ec(stu);
	i[3] = 1;
	i[4] = 0;
	line = 0;
	while ((i[5] = get_next_line(i[0], &line)) > 0)
	{
		fields = ft_strsplit(line, ' ');
		elevs = acquire_elev(fields, stu->size_y, !(stu->water), !(i[4]++)
		|| (i[4]) == stu->size_x);
		fill_ec(stu, &elevs, i[3]++);
		free_fields(fields, line, elevs);
	}
	free(line);
	if (i[5] < 0)
		return (i[5]);
	close(i[0]);
	return (i[1]);
}
