/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 00:58:13 by pcluchet          #+#    #+#             */
/*   Updated: 2018/09/12 16:06:29 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD1_H
# define MOD1_H
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# define WINX 2000
# define WINY 1000
# define POS_INCREMENT 42
# define RAIN_INCREMENT 10
# define SPEED_INCREMENT 25000
# define WAVE 0
# define RAIN 1
# define RISING_WATER 2
# define WATER 0x00ccff
# define INPUT_EXTENSION ".mod1"
typedef struct	s_cardinals
{
	int			n;
	int			s;
	int			e;
	int			w;
}				t_cardinals;

typedef struct	s_inside
{
	int			fromx;
	int			fromy;
	int			loopx;
	int			loopy;
}				t_inside;

typedef struct	s_between
{
	int			from;
	int			to;
	int			other;
}				t_between;

typedef struct	s_li
{
	int			dy;
	int			dx;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_li;

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
	float		elev;
}				t_p2d;

typedef struct	s_4triangles
{
	int			x;
	int			y;
	float		n_elev;
	float		e_elev;
	float		s_elev;
	float		w_elev;
}				t_4triangles;

typedef struct	s_f2d
{
	float		x;
	float		y;
	float		elev;
}				t_f2d;

typedef struct	s_img
{
	void		*ptr;
	char		*img_addr;
	int			line_size;
	int			endian;
	int			bits_per_pixel;
	int			x;
	int			y;
}				t_img;

typedef struct	s_stuffs
{
	int					raining_intensity;
	int					scenario;
	int					speed;
	int					raining;
	t_f2d				props;
	void				*co;
	void				*win;
	t_p2d				**map;
	t_4triangles		**watermap;
	t_p2d				**bigmap;
	int					**elevs;
	int					size_y;
	int					size_x;
	int					water_lvl;
	float				coef;
	int					linelen;
	t_img				img;
	struct s_stuffs		*water;
}				t_stuffs;

void			water_inside(t_stuffs *stuffs, int e, int w);
void			gen_watermap(t_stuffs *stuffs, char mode);
void			more_water(t_stuffs *stuffs, char mode);
char			point_in_triangle(t_p2d s, t_p2d a, t_p2d b, t_p2d c);
float			coef_between(t_stuffs *stuffs, t_p2d coords, char dir,
	int water_lvl);
float			coef_inside(t_stuffs *stuffs, t_p2d coords, t_p2d fromto,
	int water_lvl);
int				get_pixel(int x, int y, t_stuffs *stuffs);
void			malloc_bigmap(t_stuffs *s);
void			fill_bigmap(t_stuffs *s, t_coords co, float whereami,
	t_p2d pt);
void			f_fill_bigmap(t_stuffs *s, t_coords co, float whereami,
	t_p2d pt);
int				get_color_by_altitude(int n);
int				initialize(int *linenb, int *gnl, char *filename, int *fd);
float			get_max_elev(t_stuffs *stuffs);
void			malloc_buffer(int x, int y, t_stuffs *stu);
void			init_buffer(int x, int y, t_stuffs *stu);
int				line_count(t_p2d p1, t_p2d p2);
int				file_feed(char *filename, t_stuffs *stu);
void			print_point(t_p2d point);
int				line_count(t_p2d p1, t_p2d p2);
void			line_col_usr(t_p2d p1, t_p2d p2, t_stuffs *stuffs);
void			line_col(t_p2d p1, t_p2d p2, t_stuffs *stuffs);
t_p2d			f2d_to_p2d(t_f2d floatpoint);
void			set_props(t_stuffs *stu);
void			malloc_map(t_stuffs *stu);
void			malloc_watermap(t_stuffs *stu);
void			connect_dots(t_stuffs *stuffs);
t_p2d			get_elevlimits(t_stuffs *stuffs);
void			set_scale(t_stuffs *stuffs);
void			set_dots(t_stuffs *stuffs);
void			clear(t_stuffs *stuffs);
void			redraw(t_stuffs *stu);
void			redraw_water(t_stuffs *stu);
void			free_stuffs(t_stuffs *stuffs);
int				hook(int keycode, void *stuffs);
int				exit_msg(int ret_code);
void			init_line_stuffs(t_li *li, t_p2d p1, t_p2d p2);
void			next_pt_line(t_li *li, t_p2d *p1);
int				*acquire_elev(char **fields, int nbfields, int water, int side);
int				nb_fields(char **fields);
void			free_fields(char **fields, void *to_free, void *elevs);
void			set_pixel(int x, int y, int color, t_stuffs *stuffs);
void			connect_dots(t_stuffs *stuffs);
void			line(t_p2d p1, t_p2d p2, t_stuffs *s, int color);
void			special_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co);
void			special_fine_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co);
t_p2d			gen_point(t_p2d p1, t_p2d p2, float whereami);
void			set_water(t_stuffs *stuffs);
void			connect_water_dots(t_stuffs *stuffs);
void			raining(t_stuffs *stuffs);
void			gen_watermap(t_stuffs *stuffs, char mode);
void			spread_water(t_stuffs *stuffs);
void			rain_effect(t_stuffs *stuffs);
void			wave(t_stuffs *stuffs);
void			rising_water(t_stuffs *stuffs);
void			ft_triangle(t_stuffs *s, int e, int w);
void			draw_dot(t_stuffs *s, t_p2d p, int color);
void			more_water(t_stuffs *stuffs, char mode);
#endif
