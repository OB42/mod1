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


static	void	check_gnl(int gnl, char *err)
{
	if (gnl == -1)
	{
		write(2, err, ft_strlen(err));
		exit(0);
	}
}

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
		if (linenb++)
			stu->size_x = linenb - 1;
		free_fields(fields, line);
	}
	check_gnl(gnl, "gnl error\n");
	free(line);
	close(fd);
	return (0);
}

void			malloc_ec(t_stuffs *stu)
{
	int i;

	ft_printf("Parsing file...\n");
	stu->elevs = (int**)pr_malloc((stu->size_x + 1) * sizeof(int*));
	if (stu->hascolors)
		(stu->colors) = (int**)pr_malloc((stu->size_x + 1) * sizeof(int*));
	i = 1;
	while (i < stu->size_x + 1)
		(stu->elevs)[i++] = (int*)pr_malloc((stu->size_y + 1) * sizeof(int));
}

void			fill_ec(t_stuffs *stu, int **elevs, int id)
{
	int i;

	i = 0;
	while (i < stu->size_y)
		(stu->elevs)[id][i++ + 1] = (*elevs)[i];
}



int				file_feed(char *filename, t_stuffs *stu)
{
	char	*line;
	char	**fields;
	int		*elevs;
	int		i[4];

	i[0] = open(filename, O_RDONLY);
	if ((i[1] = file_test(filename, stu)))
		return (i[1]);
	malloc_ec(stu);
	i[3] = 1;
	while (get_next_line(i[0], &line))
	{
		fields = ft_strsplit(line, ' ');
		elevs = acquire_elev(fields, stu->size_y, !(stu->water));
		fill_ec(stu,&elevs, i[3]++);
		free_fields(fields, line);
		free(elevs);
	}
	free(line);
	close(i[0]);
	return (i[1]);
}
