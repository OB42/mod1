#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#define M_PI 3.14159265358979323846

void		malloc_bigmap(t_stuffs *s)
{
	int j;
	int z;

	s->bigmap = pr_malloc(sizeof(t_p2d*) * (s->size_x * s->linelen + 1));

	j = 0;
	while (j < (s->size_x * s->linelen))
	{
		s->bigmap[j] = pr_malloc(sizeof(t_p2d) * (s->size_y * s->linelen + 1));
		z = 0;
		while (z < s->size_y * s->linelen)
		{
			s->bigmap[j][z] = (t_p2d){.x = 0, .y = 0, .elev = 0, .color = 0};
			z++;
		}
		j++;
	}
}


void             line(t_p2d p1, t_p2d p2, t_stuffs *s, int color)
{
	t_li    val;
	int             line_len;

	init_line_stuffs(&val, p1, p2);
	while (1)
	{
		mlx_pixel_put(s->co, s->win, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
	}
}

void             special_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co)
{
	t_li    val;
	int             line_len;
	int cpt;
	int color;
	t_p2d   fto;
	t_p2d   midpoint;
	t_p2d   prevpoint;
	t_p2d   prevcoords;

	p1.y += p1.elev;
	p2.y += p2.elev;
	init_line_stuffs(&val, p1, p2);
	line_len = line_count(p1,p2);

	if (s->linelen == -1)
	{
		s->linelen = line_len;
		malloc_bigmap(s);
	}
	//printf("line len =%d\n",line_len);
	cpt = 0;
	t_p2d dpoint;


	fto = set_fromto(s, p1, p2);
	while (1)
	{
		float whereami = ((float)cpt/(float)line_len);

		float coef = whereami;
		float sinuscorrect = -(M_PI/2.0);
		int elevnow = ((float)p2.elev - (float)p1.elev);
		if (p2.elev < p1.elev)
		{
			elevnow = ((float)p1.elev - (float)p2.elev);
			coef = 1.0 - whereami;
			sinuscorrect = M_PI/2.0;
		}
		float sinelev =  sin(whereami * M_PI +  sinuscorrect)+1.0;

		dpoint = p1;
		dpoint.y -=  fabs(sinelev/2.0 * ((float)elevnow));
		if (p1.elev != 0 &&  p2.elev != 0)
		{

			if (p2.elev > p1.elev)
				dpoint.y -=  abs(p1.elev) ;
			else
				dpoint.y -=  abs(p2.elev) ;
		}
		int a;
		int b;

		a = 0;
		b = 0;
		//bigmap setting:
		//int posinow = whereami * (float)line_len;
		if (1)
		{
			prevcoords = (t_p2d){.x = a, .y = b};
			if (co.x1 == co.x2)
			{
				a = (co.x1 - 1) * line_len;
				b = ((co.y1 - 1) * line_len) + whereami * s->linelen;
			}
			else
			{
				b = (co.y1 - 1) * line_len;
				a = ((co.x1 - 1) * line_len) + whereami * s->linelen;
			}
			if (co.x1 < 2)
			{
				//printf("setting big map [%d][%d].elev = %d\n",a,b, dpoint.y - p1.y);
			}
			s->bigmap[a][b] = dpoint;
			s->bigmap[a][b].elev = p1.y - dpoint.y ;//abs(dpoint.y - p1.y);
		}


		float red = fto.y + ((fto.x - fto.y)) * whereami;
		color = get_color(0, red, 128 - (red/2));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		prevpoint = p1;
		next_pt_line(&val, &p1);
		cpt++;
	}
}

void             special_fine_line(t_p2d p1, t_p2d p2, t_stuffs *s, t_coords co)
{
	t_li    val;
	int             line_len;
	int cpt;
	int color;
	t_p2d   fto;

	p1.y += p1.elev;
	p2.y += p2.elev;
	init_line_stuffs(&val, p1, p2);
	line_len = line_count(p1,p2);
	cpt = 0;
	t_p2d dpoint;
	fto = set_fromto(s, p1, p2);
	while (1)
	{
		float whereami = ((float)cpt/(float)line_len);
		float coef = whereami;
		float sinuscorrect = -(M_PI/2.0);
		int elevnow = ((float)p2.elev - (float)p1.elev);
		if (p2.elev < p1.elev)
		{
			elevnow = ((float)p1.elev - (float)p2.elev);
			coef = 1 - whereami;
			sinuscorrect = (M_PI/2.0);
		}
		float sinelev = sin(whereami * M_PI +  sinuscorrect)+1;
		dpoint = p1;
		dpoint.y -= fabs(sinelev * (elevnow/2));
		if (p1.elev != 0 &&  p2.elev != 0)
		{
			if (p2.elev > p1.elev)
				dpoint.y -=  abs(p1.elev) ;
			else
				dpoint.y -=  abs(p2.elev) ;
		}

		float red = fto.y + ((fto.x - fto.y)) * whereami;
		int a;
		int b;
		if (co.x1 == co.x2)
		{
			a = (co.x1 ) ;
			b = ((co.y1 ) ) + whereami * s->linelen;
		}
		else
		{
			b = (co.y1 ) ;
			a = ((co.x1 ) ) + whereami * s->linelen;
		}
		if (s->bigmap[a][b].x ==0)
		{
			s->bigmap[a][b] = dpoint;
			s->bigmap[a][b].elev = abs(dpoint.y - p1.y);
			s->bigmap[a][b].color = -1;
		}
		color = get_color(0, red, 128 - (red/2));

		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		next_pt_line(&val, &p1);
		cpt++;
	}
}

void	connect_fne_dots(t_stuffs *stuffs)
{
		int		e;
		int		w;
		float	max_elev;
		int		color;

		max_elev = get_max_elev(stuffs);
		e = 0 * stuffs->linelen;
		ft_printf("Rendering fine dots..\n");

		//while (stuffs->bigmap[e])
	 	int i = 0;
		while (e < (stuffs->size_x * stuffs->linelen))
		{
			w = 0 * stuffs->linelen;
	//		while (stuffs->bigmap[e][w])
			while (w < (stuffs->size_y * stuffs->linelen))
			{

				if ((stuffs->bigmap)[e][w].elev >= 0 )
				{
					color = get_color_by_altitude(stuffs->bigmap[e][w].elev, max_elev);
					t_p2d cheat;
					cheat = (stuffs->bigmap)[e][w];
					cheat.y += 8;
					line((stuffs->bigmap)[e][w], cheat, stuffs,color);
				}

				w++;
				//w += stuffs->linelen;
			}
			//e += stuffs->linelen;
			e++;
		}


		ft_printf("Done %i!\n", stuffs->linelen);
		//	connect_ufine_dots(stuffs);
}

void	connect_fine_dots(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 0;
	ft_printf("Rendering fine dots...\n");
	while (e < ((stuffs->size_x - 1)* stuffs->linelen))
		{
			w = 0;
	//		while (w < (9 * stuffs->linelen))
			while ((w < (stuffs->size_y - 1) * stuffs->linelen))
			{
				if (w != stuffs->size_y * stuffs->linelen)
				{
					if ((stuffs->bigmap)[e][w].x != 0 &&
							(stuffs->bigmap)[e][ w + stuffs->linelen - (w % stuffs->linelen)].x > 0 &&
							(stuffs->bigmap)[e][w].color != -1 &&
							(stuffs->bigmap)[e][ w + stuffs->linelen - (w % stuffs->linelen)].color != -1)
					{
						special_fine_line((stuffs->bigmap)[e][w],
								(stuffs->bigmap)[e][w + stuffs->linelen - (w %stuffs->linelen)],
								stuffs,
								(t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = w + stuffs->linelen - (w % stuffs->linelen) });
					}
				}
				if (e != stuffs->size_x)
				{
					if (
							(stuffs->bigmap)[e][w].x != 0 &&
							(stuffs->bigmap)[e + stuffs->linelen - (e % stuffs->linelen)][ w].x != 0 &&
					(stuffs->bigmap)[e][w].color != -1 &&
	(stuffs->bigmap)[e + stuffs->linelen - (e % stuffs->linelen)][ w].color != -1

					   )
					{
						special_fine_line((stuffs->bigmap)[e][w],
								(stuffs->bigmap)[e + stuffs->linelen - (e % stuffs->linelen)][w ]
								, stuffs,
								(t_coords){.x1 = e, .y1 = w, .x2 = e + stuffs->linelen - (e % stuffs->linelen), .y2 = w });
					}
				}
				w++;
			}
			e++;
		}
	ft_printf("Done !\n\n");
	connect_fne_dots(stuffs);
}

void	connect_dots(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 1;
	ft_printf("Rendering dots...\n");
	while (e <= stuffs->size_x)
	{
		w = 1;
		while (w <= stuffs->size_y)
		{
			if (w != stuffs->size_y)
			{
				special_line((stuffs->map)[e][w], (stuffs->map)[e][w + 1], stuffs,
						(t_coords){.x1 = e, .y1 = w, .x2 = e, .y2 = w + 1});
			}
			if (e != stuffs->size_x)
			{
				special_line((stuffs->map)[e][w], (stuffs->map)[e + 1][w], stuffs,
						(t_coords){.x1 = e, .y1 = w, .x2 = e + 1, .y2 = w });
			}
			w++;
		}
		e++;
	}
	ft_printf("Done !\n\n");
	connect_fine_dots(stuffs);
}

void	detailed_point(t_stuffs *s, int ie, int je, t_f2d noww)
{
	int		r;
	t_f2d	temp;
	int		col;

	col = 0xFFFFFF;
	r = (float)(s->elevs)[gorx(s, ie)][gory(s, je)] * s->coef;
	if (s->hascolors)
		col = (s->colors)[gorx(s, ie)][gory(s, je)];
	altinfos_set(s, r);
	temp = (t_f2d){.x = noww.x + s->props.x * je,
		.y = (noww.y + s->props.y * je) - r, .elev = r};
	temp.color = col;
	je++;
	s->map[ie][je - 1] = f2d_to_p2d(temp);
}

void	set_dots(t_stuffs *s)
{
	int		r;
	t_p2d	p1;
	int		nb[3];
	t_f2d	noww;
	t_f2d	temp;

	p1 = (t_p2d){.x = 400, .y = 100, .color = 0xFF00FF };
	nb[0] = 1;
	ft_printf("Calculating dots...\n");
	while (nb[0] <= s->size_x)
	{
		nb[1] = 1;
		r = (float)(s->elevs)[gorx(s, nb[0])][gory(s, nb[1])] * s->coef;
		if (s->hascolors)
			nb[2] = (s->colors)[gorx(s, nb[0])][gory(s, nb[1])];
		altinfos_set(s, r);
		noww = (t_f2d){.x = p1.x - (s->props.x * nb[0]),
			.y = (p1.y + s->props.y * nb[0]), .elev = 0 };
		temp = (t_f2d){.x = noww.x, .y = noww.y - r, .elev = r};
		temp.color = nb[2];
		s->map[nb[0]][nb[1]] = f2d_to_p2d(temp);
		while (nb[1] <= s->size_y)
			detailed_point(s, nb[0], nb[1]++, noww);
		nb[0]++;
	}
}

void	clear(t_stuffs *stuffs)
{
	int i;
	int j;

	i = 0;
	while (i < WINX)
	{
		j = 0;
		while (j < WINY)
		{
			mlx_pixel_put(stuffs->co, stuffs->win, i, j, 0x000000);
			j++;
		}
		i++;
	}
}
