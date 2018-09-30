/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by obenazzo          #+#    #+#             */
/*   Updated: 2017/02/15 06:30:56 by obenazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	free_line(char **coor, char *line)
{
	int i;

	i = 0;
	while (coor[i])
		free(coor[i++]);
	free(coor);
	free(line);
}

void	parse_points(int fd, char **line, t_stuffs *stuffs)
{
	char	**s;
	int		g;
	t_p2d	tmp;

	while ((g = get_next_line(fd, line)) > 0)
	{
		s = ft_strsplit(*line, ' ');
		if (!s[0] || !s[1] || !s[2] || s[3])
			print_error("invalid map\n");
		tmp = (t_p2d){ft_atoi(s[0]) + 1, ft_atoi(s[1]) + 1,
			(float)ft_atoi(s[2])};
		if (tmp.x >= stuffs->size_x || tmp.y >= stuffs->size_y
			|| (tmp.x < 2) || (tmp.y < 2) || tmp.elev > 200 || tmp.elev < 0)
			print_error("invalid map\n");
		stuffs->elevs[tmp.x][tmp.y] = !stuffs->water ? 0 : (int)tmp.elev;
		free_line(s, *line);
	}
	free(*line);
	if (g < 0)
		print_error("gnl error\n");
}

void	parse_dimensions(int fd, char **line, t_stuffs *stuffs)
{
	char	**s;

	if (get_next_line(fd, line) < 1)
		print_error("gnl error\n");
	s = ft_strsplit(*line, ' ');
	if (!s[0] || !s[1] || s[2])
		print_error("invalid map\n");
	stuffs->size_x = ft_atoi(s[0]);
	stuffs->size_y = ft_atoi(s[1]);
	if (stuffs->size_x > 25 || stuffs->size_y > 25
		|| stuffs->size_x < 2 || stuffs->size_y < 2)
		print_error("the map is invalid\n");
	free_line(s, *line);
}

void	malloc_ec(t_stuffs *stu)
{
	int i;

	ft_printf("Parsing file...\n");
	stu->elevs = (int**)pr_malloc((stu->size_x + 1) * sizeof(int*));
	i = 1;
	while (i < stu->size_x + 1)
	{
		(stu->elevs)[i] = (int*)pr_malloc((stu->size_y + 1) * sizeof(int));
		ft_bzero((stu->elevs)[i], (stu->size_y + 1) * sizeof(int));
		i++;
	}
}

void	gen_map(char *filename, t_stuffs *stuffs)
{
	char	*line;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		print_error("error can't open file\n");
	line = 0;
	parse_dimensions(fd, &(line), stuffs);
	malloc_ec(stuffs);
	line = 0;
	parse_points(fd, &(line), stuffs);
	close(fd);
}
