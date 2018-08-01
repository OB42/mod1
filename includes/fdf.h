/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 00:58:13 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 11:07:14 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# define WINX 2000
# define WINY 1000
# define POS_INCREMENT 42

typedef struct	s_li
{
	int			dy;
	int			dx;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_li;

typedef struct	s_p3d
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_p3d;

typedef struct	s_coords
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;
}				t_coords;

typedef struct	s_p2d
{
	int			x;
	int			y;
	int			elev;
	int			color;
}				t_p2d;

typedef struct	s_f2d
{
	float		x;
	float		y;
	int			elev;
	int			color;
}				t_f2d;

typedef struct	s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;


typedef struct	s_img
{
	void			*ptr;
	char			*img_addr;
	int				line_size;
	int				endian;
	int				bits_per_pixel;
	int				x;
	int				y;
}				t_img;

typedef struct	s_stuffs
{
	t_p2d		altinfos;
	t_f2d		props;
	void		*co;
	void		*win;
	t_p2d		**map;
	t_p2d		**bigmap;
	int			**elevs;
	int			**colors;
	int			size_y;
	int			size_x;
	char		hascolors;
	char		ogcolors;
	int			viewpoint;
	float		coef;
	int			linelen;
	t_img		img;
}				t_stuffs;

int				get_color_by_altitude(int n);
int				initialize(int *linenb, int *gnl, char *filename, int *fd);
float			get_max_elev(t_stuffs *stuffs);
int				abs(int x);
void			malloc_buffer(int x, int y, t_stuffs *stu);
void			init_buffer(int x, int y, t_stuffs *stu);
void			add_pt_buffer(t_stuffs *stu, t_p2d pt);
int				line_count(t_p2d p1, t_p2d p2);
void			line_color(t_p2d p1, t_p2d p2, t_stuffs *stuffs, t_p2d altinfo);
int				get_color(int r, int g, int b);
int				file_feed(char *filename, t_stuffs *stu);
void			print_point(t_p2d point);
int				get_color(int r, int g, int b);
t_rgb			int_to_rgb(int col);
int				line_count(t_p2d p1, t_p2d p2);
void			line_col_usr(t_p2d p1, t_p2d p2, t_stuffs *stuffs);
void			line_col(t_p2d p1, t_p2d p2, t_stuffs *stuffs);
t_p2d			f2d_to_p2d(t_f2d floatpoint);
void			set_props(t_stuffs *stu);
void			malloc_map(t_stuffs *stu);
void			altinfos_set(t_stuffs *stu, int r);
void			connect_dots(t_stuffs *stuffs);
int				gory(t_stuffs *stuffs, int index);
int				gorx(t_stuffs *stuffs, int index);
t_p2d			get_elevlimits(t_stuffs *stuffs);
void			set_scale(t_stuffs *stuffs);
void			set_dots(t_stuffs *stuffs);
void			clear(t_stuffs *stuffs);
void			redraw(t_stuffs *stu, int vp);
void			free_stuffs(t_stuffs *stuffs);
int				hook(int keycode, void *stuffs);
int				exit_msg(int ret_code);
int				rgb_to_int(t_rgb col);
t_p2d			set_fromto(t_stuffs *s, t_p2d p1, t_p2d p2);
void			init_line_stuffs(t_li *li, t_p2d p1, t_p2d p2);
void			next_pt_line(t_li *li, t_p2d *p1);
char			has_color(char **fields, int nbfields);
int				parse_color(char *field);
unsigned char	twochar_to_byte(char a, char b);
int				*acquire_elev(char **fields, int nbfields);
int				nb_fields(char **fields);
int				*acquire_colors(char **fields, int nbfields);
void			free_fields(char **fields, void *to_free);
void			set_hascol(t_stuffs *stu, int has);
void			set_pixel(int x, int y, int color, t_stuffs *stuffs);
void			connect_dots(t_stuffs *stuffs);
void			line(t_p2d p1, t_p2d p2, t_stuffs *s, int color);
void			special_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co);
void			special_fine_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co);
#endif
