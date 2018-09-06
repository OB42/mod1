/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 02:36:32 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/15 06:30:56 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

//OPTI BENCHMARK
//to remove
#include <sys/time.h>
/////////////////////

void	init_img(t_stuffs *stuffs)
{
	stuffs->img.ptr = mlx_new_image(stuffs->co, WINX, WINY);
	stuffs->img.line_size = WINX * 4;
	stuffs->img.endian = 0;
	stuffs->img.bits_per_pixel = 32;
	stuffs->img.y = 0;
	stuffs->img.x = 0;
	stuffs->img.img_addr = mlx_get_data_addr(stuffs->img.ptr,
			&(stuffs->img.bits_per_pixel), &(stuffs->img.line_size), &(stuffs->img.endian));
}

int	init(t_stuffs *stuffs, char *path)
{
	stuffs->raining_intensity = 100;
	stuffs->coef = 1;
	stuffs->raining = 0;
	stuffs->linelen = -1;
	if (exit_msg(file_feed(path, stuffs)))
		return (1);
	set_props(stuffs);
	set_scale(stuffs);
	malloc_map(stuffs);
	malloc_watermap(stuffs);
	if (stuffs->water)
	{
		stuffs->co = mlx_init();
		stuffs->win = mlx_new_window(stuffs->co, WINX, WINY, "Test");
		init_img(stuffs);
	}
	set_dots(stuffs);
	connect_dots(stuffs);
	return (0);
}

void	move_water(t_stuffs *stuffs, t_p2d *from, t_p2d *to, float quantity)
{

	from->elev -= quantity;
	// from->y += quantity * stuffs->coef;
	to->elev += quantity;
	// to->y -= quantity * stuffs->coef;
}

void	spread_water(t_stuffs *stuffs)
{
	int		e;
	int		w;
	int		x;
	int		y;
	t_p2d	max;
	int		z = 0;
	static int r = 0;
	int i;
	static	float	**current = 0;
	static t_p2d n[4] = {
		(t_p2d){.x = 1, .y = 0},
		(t_p2d){.x = 0, .y = -1},
		(t_p2d){.x = 0, .y = 1},
		(t_p2d){.x = -1, .y = 0},
	};
	float temp = 0;

	if (!current)
	{
		current = pr_malloc(sizeof(float*) * (stuffs->size_x * stuffs->linelen + 1));
		e = 0;
		while (e < ((stuffs->size_x) * stuffs->linelen))
			current[e++] = pr_malloc(sizeof(float) * (stuffs->size_y * stuffs->linelen + 1));
	}
	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while ((w < (stuffs->size_y) * stuffs->linelen))
		{
			current[e][w] = stuffs->water->bigmap[e][w].elev;
			w++;
		}
		e++;
	}
	float dec = 1;
	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while (w < (stuffs->size_y) * stuffs->linelen)
		{
			if (stuffs->water->bigmap[e][w].elev > dec * 0.99)
			{
				max.y = -1;
				max.x = -1;
				max.elev = 0;
				i = 0;
				int multi = 0;
				while (i < 4)
				{
					x = n[i].x + e;
					y = n[i].y + w;
					if (x > -1 && y > -1 && x < (stuffs->size_x) * stuffs->linelen && y < (stuffs->size_y) * stuffs->linelen)
					{
						temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[x][y].elev + current[x][y]);
						if (temp > max.elev)
						{
							max.x = x;
							max.y = y;
							// if (temp < max.elev + 0.1)
							// 	multi++;
							// else
							// 	multi = 0;
							max.elev = temp;
						}
					}
					i++;
				}
				if (max.elev > dec - 0.01)
				{
					int d = multi ? dec : dec / (multi + 1);
					i = 0;
					while (i < 4)
					{
						x = n[i].x + e;
						y = n[i].y + w;
						if (x > -1 && y > -1 && x < (stuffs->size_x) * stuffs->linelen && y < (stuffs->size_y) * stuffs->linelen)
						{
							temp = (stuffs->bigmap[e][w].elev + current[e][w]) - (stuffs->bigmap[x][y].elev + current[x][y]);
							if (temp > max.elev * 0.99)
								move_water(stuffs, &(stuffs->water->bigmap[e][w]), &(stuffs->water->bigmap[x][y]), dec);
							// if (stuffs->water->bigmap[e][w] < dec * 0.99)
							// {
							// 	break;
							// }
						}
						i++;
					}
				}
			}
			w++;
		}
		e++;
	}
}

void	raining(t_stuffs *stuffs)
{
	int			i;
	int			e;
	int			w;
	static int r = 0;

	i = 0;
	while (i++ < 100)
		spread_water(stuffs);
	// if (!(r++))
	e = 0;
	{
		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;
			while ((w < (stuffs->size_y) * stuffs->linelen))
			{
				if (stuffs->raining_intensity && rand() % (stuffs->raining_intensity / 2 + 1) == 0)
					stuffs->water->bigmap[e][w].elev += 1;
				w++;
			}
			e++;
		}
	}
	redraw(stuffs);
	printf("ok\n");
}

void	rising_water(t_stuffs *stuffs)
{
	int			i;
	int			e;
	int			w;
	static int r = 0;

	i = 0;
	e = 0;
	/*
	   if (!r)
	   {
	   while (e < ((stuffs->size_x) * stuffs->linelen))
	   {
	   w = 0;
	   while (w < ((stuffs->size_y) * stuffs->linelen))
	   {
	   int	k =  1;
	//				if (stuffs->bigmap[e][w].elev >= k)
	//				stuffs->bigmap[e][w].elev -= k;
	w++;
	}
	e++;
	}
	r = 1;
	}
	//	if ((r++) % 2 == 0)
	*/
	{
		e = 0;
		//stuffs->water->bigmap[(stuffs->size_x) * stuffs->linelen - 32 - 1][0].elev += 100;
		//	 	stuffs->water->bigmap[0][0].elev += 10;

		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;


			while (w < ((stuffs->size_y) * stuffs->linelen)  ||  stuffs->water->bigmap[e][w].elev > 0.1)
			{

				/*
				   int sr = 0;
				   if (r %4 == 0)
				   sr = 5;
				   */

				//if (r % 5 == 0 && r <= 200)
				//stuffs->water->bigmap[e][w].elev += 1;
				if ((r < 5) || (stuffs->bigmap[e][w].elev < (r % 100)))
				{
					if (w < (5 * r) || e < 90 || e > ((stuffs->size_x) * stuffs->linelen) - 90 )
						stuffs->water->bigmap[e][w].elev = (r % 100) -  stuffs->bigmap[e][w].elev;//(r % 100) ;

				}


				w++;
			}

			w = ((stuffs->size_y) * stuffs->linelen) - 90;
			while (w > 0 && w > (((stuffs->size_y) * stuffs->linelen) - 5 * r) ||  stuffs->water->bigmap[e][w].elev > 0.1)
			{

				/*
				   int sr = 0;
				   if (r %4 == 0)
				   sr = 5;
				   */

				//if (r % 5 == 0 && r <= 200)
				//stuffs->water->bigmap[e][w].elev += 1;
				if (r < 5 || (stuffs->bigmap[e][w].elev < (r % 100)))
					stuffs->water->bigmap[e][w].elev = (r % 100) -  stuffs->bigmap[e][w].elev;//(r % 100) ;

				w--;
			}

			e++;
		}
	}


	r++;
	while (i++ < 50)
		spread_water(stuffs);

	e = 0;
	// if ((r++) % 4 == 0)



	redraw_water(stuffs);

}

char water_nearby(t_stuffs *stuffs, int e, int w, int waterlevel)
{
	int i;
	int j;	

	i = e - 90;
	while (i > 0 && i < ((stuffs->size_x) * stuffs->linelen) && i < e + 90)
	{
		j = w - 90;
		while (j > 0 && j < ((stuffs->size_y) * stuffs->linelen) && j < w + 90)
		{
			if (stuffs->bigmap[i][j].elev > waterlevel)
				break;

			if (stuffs->water->bigmap[i][j].elev >= 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);

}


void    reset_xwatermap(t_stuffs *stuffs)
{
	int e;
	int w;

	e = 1;
	while (e <= stuffs->size_x)
	{
		w = 1;
		while (w <= stuffs->size_y)
		{
			stuffs->watermap[e][w].x = 0;
			w++;
		}
		e++;
	}
}


float    highest_point(t_stuffs *stuffs, t_p2d coords)
{
	int e;
	float max;
	int w;


	max = 0.0;
	e = (coords.x - 1) * 100;
	while (e < (coords.x ) * 100 && e < (stuffs->size_x * stuffs->linelen) )
	{
		w = (coords.y - 1) * 100;
		while (w < (coords.y ) * 100 && w < (stuffs->size_y * stuffs->linelen))
		{
			if (stuffs->bigmap[e][w].elev > max)
			{
				max = stuffs->bigmap[e][w].elev; 
			}
			w++;
		}
		e++;
	}
	return max;
}



float coef_between(t_stuffs *stuffs, t_p2d coords, char dir, int water_lvl)
{
	int from;
	int to;
	int other;
	int i;
	int cpt;



	//if ((int)highest_point(stuffs, coords) > water_lvl)
	//	return 0.0;

	cpt = 0;
	if (dir == 'S')
	{
		from = (coords.x - 1) * (stuffs->linelen);
		to = (coords.x ) * (stuffs->linelen);
		other = (coords.y) * (stuffs->linelen);

		if (other < (stuffs->size_y * stuffs->linelen) && (to < (stuffs->size_x * stuffs->linelen)))
		{
			i = from;
			while (i < to && other < (stuffs->size_x * stuffs->linelen))
			{
				if (stuffs->bigmap[i][other].elev < water_lvl)
					cpt++;
				i++;
			}
		}

	}
	printf("between coef : %f\n", ((float)cpt)/(stuffs->linelen) );
	return ((float)cpt)/(stuffs->linelen);
}

float coef_inside(t_stuffs *stuffs, t_p2d coords, t_p2d fromto, int water_lvl)
{
	t_p2d from;
	int cpt;
	int i;

	//return 0.0;
	//
	

	cpt = 0;
	if (fromto.x == 'N')
	{
		if (fromto.y == 'E')		
		{
		printf("TO EAST FROM NORTH");
			from.x = (coords.x - 1) * stuffs->linelen;
			from.y = (coords.y - 1) * stuffs->linelen;

			i = 0;
			while ( (i < (stuffs->linelen / 2)) &&
			 from.x + i < (stuffs->size_x * stuffs->linelen)  &&  
			 from.y + i < (stuffs->size_y * stuffs->linelen)  
			      )
			{
				if (stuffs->bigmap[from.x + i][from.y + i].elev < water_lvl)
						cpt++;
				i++;
			}
		}
		else if (fromto.y == 'W')
		{
			//return (0.0);
			//
		printf("TO WEST FROM NORTH");

			from.x = (coords.x) * stuffs->linelen;
			from.y = (coords.y - 1) * stuffs->linelen;


			i = 0;
			while ( (i < (stuffs->linelen / 2)) &&

			 from.x - i < (stuffs->size_x * stuffs->linelen)  &&  
			 from.x - i > 0  &&  
			 from.y + i < (stuffs->size_y * stuffs->linelen)  
			      )
			{
				if (stuffs->bigmap[from.x - i][from.y + i].elev < water_lvl)
						cpt++;
				i++;
			}
		}
	}
	if (fromto.x == 'W')
	{

	printf("TO SOUTHi FROM WEST");
		if (fromto.y == 'S')		
		{
			from.x = (coords.x ) * stuffs->linelen;
			from.y = (coords.y ) * stuffs->linelen;

			i = 0;
			while ( (i < (stuffs->linelen / 2)) &&
			 from.x - i < (stuffs->size_x * stuffs->linelen)  &&  
			 from.y - i < (stuffs->size_y * stuffs->linelen)  
			      )
			{
				if (stuffs->bigmap[from.x - i][from.y - i].elev < water_lvl)
						cpt++;
				i++;
			}
		}
	}
	if (fromto.x == 'E')
	{

	printf("TO SOUTH FROM EAST");
		if (fromto.y == 'S')		
		{
			from.x = (coords.x - 1) * stuffs->linelen;
			from.y = (coords.y) * stuffs->linelen;

			i = 0;
			while ( (i < (stuffs->linelen / 2)) &&
			 from.x + i < (stuffs->size_x * stuffs->linelen)  &&  
			 from.y - i < (stuffs->size_y * stuffs->linelen)  
			      )
			{
				if (stuffs->bigmap[from.x + i][from.y - i].elev < water_lvl)
						cpt++;
				i++;
			}
		}
	}

	printf("case [%d][%d] -> cpt = %d\n",coords.x, coords.y, cpt);
	float ret = ( ((float)cpt)/ (stuffs->linelen / 2.0) - 0.0);
	if (ret < 0)
		ret = 0.0;

	printf("coef : %f\n",  ret  );
	return (ret);

/*
	cpt = 0;
	if (dir == 'S')
	{
		from = (coords.x - 1) * 100;
		to = (coords.x ) * 100;
		other = (coords.y) * 100;

		if (other < (stuffs->size_y * stuffs->linelen) && (to < (stuffs->size_x * stuffs->linelen)))
		{
			i = from;
			while (i < to && other < (stuffs->size_x * stuffs->linelen))
			{
				if (stuffs->bigmap[i][other].elev < water_lvl)
					cpt++;
				i++;
			}
		}

	}
	printf("coef : %f\n", ((float)cpt)/100.0 );
	return ((float)cpt)/100.0;
*/
}




void    wave_watermap(t_stuffs *stuffs)
{
	static char k = 0;
	int e;
	int w;
	float oldelev;
	float temp;
	sleep(1);

	//reset_xwatermap(stuffs);

	e = 1;
	if (!k)
	{
		while (e <= stuffs->size_x)
		{
			stuffs->watermap[e][1].N_elev =  10;
			e++;
		}
		k = 1;
	}
	else
	{
		while (e < stuffs->size_x)
		{

			w = 1;
			while (w <= stuffs->size_y)
			{
				//if (stuffs->watermap[e][w].N_elev > 0)
				{
					stuffs->watermap[e][w].E_elev += 
				stuffs->watermap[e][w].N_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'N', .y = 'E'}, stuffs->watermap[e][w].N_elev);
					if ( stuffs->watermap[e][w].E_elev > stuffs->watermap[e][w].N_elev  )
						stuffs->watermap[e][w].E_elev = stuffs->watermap[e][w].N_elev;  

					stuffs->watermap[e][w].W_elev += 
				stuffs->watermap[e][w].N_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'N', .y = 'W'}, stuffs->watermap[e][w].N_elev);
					if ( stuffs->watermap[e][w].W_elev > stuffs->watermap[e][w].N_elev  )
						stuffs->watermap[e][w].W_elev = stuffs->watermap[e][w].N_elev;  

					stuffs->watermap[e][w].S_elev +=  
				(stuffs->watermap[e][w].E_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'E', .y = 'S'}, stuffs->watermap[e][w].E_elev))
				+( stuffs->watermap[e][w].W_elev * coef_inside(stuffs, (t_p2d){.x = e, .y = w}, (t_p2d){.x = 'W', .y = 'S'}, stuffs->watermap[e][w].W_elev)) ;
					if ( stuffs->watermap[e][w].S_elev > stuffs->watermap[e][w].E_elev  )
						stuffs->watermap[e][w].S_elev = fmax(stuffs->watermap[e][w].E_elev, stuffs->watermap[e][w].W_elev);  


				}


					if ( w + 1 <= stuffs->size_y)
					{
						//if (stuffs->bigmap[((e) * stuffs->linelen) - 50][ ((w) * stuffs->linelen) - 50].elev <
						//		stuffs->watermap[e][w].elev )

						{
							stuffs->watermap[e][w + 1].N_elev += 
								stuffs->watermap[e][w].S_elev * 
								coef_between(stuffs, (t_p2d){.x = e, .y = w},'S', stuffs->watermap[e][w].S_elev);
							if ( stuffs->watermap[e][w + 1].N_elev > stuffs->watermap[e][w].S_elev )
								stuffs->watermap[e][w + 1].N_elev = stuffs->watermap[e][w].S_elev;
							//stuffs->watermap[e][w + 1].x = 1;
						}

					}
				w++;
			}
			e++;
		}

	}
}


char point_inside_triangle(t_p2d s, t_p2d a, t_p2d b, t_p2d c)
{
	int as_x = s.x - a.x;
	int as_y = s.y - a.y;

	char s_ab = (b.x-a.x)*as_y-(b.y-a.y)*as_x > 0;

	if((c.x-a.x)*as_y-(c.y-a.y)*as_x > 0 == s_ab) return 0;

	if((c.x-b.x)*(s.y-b.y)-(c.y-b.y)*(s.x-b.x) > 0 != s_ab) return 0;

	return 1;
}

void	wave(t_stuffs *stuffs)
{
	int			i;
	int			e;
	int			w;
	static int r = 0;

	i = 0;
	e = 0;


	//opti
	////////////////////////////
	struct timeval time;
	gettimeofday(&time, NULL);
	long start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////

	{
		e = 0;
		//stuffs->water->bigmap[(stuffs->size_x) * stuffs->linelen - 32 - 1][0].elev += 100;
		//	 	stuffs->water->bigmap[0][0].elev += 10;

		/*
		   while (e < ((stuffs->size_x) * stuffs->linelen))
		   {
		   w = 0;
		   while (w < ((stuffs->size_y) * stuffs->linelen) && w < (5 * r) ||  stuffs->water->bigmap[e][w].elev > 0.1)
		   {


		//if (r % 5 == 0 && r <= 200)
		//stuffs->water->bigmap[e][w].elev += 1;
		if (r < 5 || (stuffs->bigmap[e][w].elev < (r % 100)))
		{
		stuffs->water->bigmap[e][w].elev = (r % 100) -  stuffs->bigmap[e][w].elev;//(r % 100) ;
		stuffs->water_lvl = (r % 100);
		}

		w++;
		}
		e++;
		}
		*/


		//stuffs->watermap[1][2].elev = 10;

		wave_watermap(stuffs);

		while (e < ((stuffs->size_x) * stuffs->linelen))
		{
			w = 0;
			while (w < ((stuffs->size_y) * stuffs->linelen))
			{

				//NORTH TRIANGLE
				if (point_inside_triangle( (t_p2d){.x = e, .y = w}, 
							(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w - (w % stuffs->linelen))},
							(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w - (w % stuffs->linelen))},
							(t_p2d){.x = (e - (e % stuffs->linelen) +  (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) +  (stuffs->linelen / 2))}
							))
				{

					stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e/stuffs->linelen) + 1][(w/stuffs->linelen) + 1].N_elev  - stuffs->bigmap[e][w].elev;
				}

				//SOUTH TRIANGLE
				else if (point_inside_triangle( (t_p2d){.x = e, .y = w}, 
							(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w + (stuffs->linelen - (w % stuffs->linelen)))},
							(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w + (stuffs->linelen -(w % stuffs->linelen)))},
							(t_p2d){.x = (e - (e % stuffs->linelen) +  (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) +  (stuffs->linelen / 2))}
							))
				{

					stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e/stuffs->linelen) + 1][(w/stuffs->linelen) + 1].S_elev  - stuffs->bigmap[e][w].elev;
				}

				//EAST TRIANGLE
				else if (point_inside_triangle( (t_p2d){.x = e, .y = w}, 
							(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w - (w % stuffs->linelen))},
							(t_p2d){.x = (e - (e % stuffs->linelen)), .y = (w + (stuffs->linelen - (w % stuffs->linelen)))},
							(t_p2d){.x = (e - (e % stuffs->linelen) +  (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) +  (stuffs->linelen / 2))}
							))
				{

					stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e/stuffs->linelen) + 1][(w/stuffs->linelen) + 1].E_elev  - stuffs->bigmap[e][w].elev;
				}

				//WEST TRIANGLE
				else if (point_inside_triangle( (t_p2d){.x = e, .y = w}, 
							(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w - (w % stuffs->linelen))},
							(t_p2d){.x = (e + (stuffs->linelen - (e % stuffs->linelen))), .y = (w + (stuffs->linelen -(w % stuffs->linelen)))},
							(t_p2d){.x = (e - (e % stuffs->linelen) +  (stuffs->linelen / 2)), .y = (w - (w % stuffs->linelen) +  (stuffs->linelen / 2))}
							))
				{

					stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e/stuffs->linelen) + 1][(w/stuffs->linelen) + 1].W_elev  - stuffs->bigmap[e][w].elev;
				}



				/*
				   if ((stuffs->bigmap[e][w].elev < stuffs->watermap[(e/stuffs->linelen) + 1][(w/stuffs->linelen) + 1].elev))
				   {
				   stuffs->water->bigmap[e][w].elev = stuffs->watermap[(e/stuffs->linelen) + 1][(w/stuffs->linelen) + 1].elev - stuffs->bigmap[e][w].elev;
				   }


*/

				/*
				//if (r % 5 == 0 && r <= 200)
				//stuffs->water->bigmap[e][w].elev += 1;
				if (r < 5 || (stuffs->bigmap[e][w].elev < (r % 100)))
				{
				stuffs->water->bigmap[e][w].elev = (r % 100) -  stuffs->bigmap[e][w].elev;//(r % 100) ;
				stuffs->water_lvl = (r % 100);
				}
				*/

				w++;
			}
			e++;
		}

	}

	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	long end = (time.tv_sec * 1000) + (time.tv_usec / 1000);


	long spent = end - start;
	printf("water propag took %ld ms\n", spent);
	/////////////////////////////






	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////

	r++;
	   while (i++ < 50)
	   spread_water(stuffs);

	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);


	spent = end - start;
	printf("water spread took %ld ms\n", spent);
	/////////////////////////////


	e = 0;
	// if ((r++) % 4 == 0)



	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////

	redraw_water(stuffs);

	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);


	spent = end - start;
	printf("redraw took %ld ms\n", spent);
	/////////////////////////////


}
int	water_loop(void *stuffs)
{
	//opti
	////////////////////////////
	struct timeval time;
	gettimeofday(&time, NULL);
	long start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////



	if (((t_stuffs *)stuffs)->scenario == WAVE)
		wave(stuffs);
	else if (((t_stuffs *)stuffs)->scenario == RAIN)
		raining(stuffs);
	else if (((t_stuffs *)stuffs)->scenario == RISING_WATER)
		rising_water(stuffs);



	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	long end = (time.tv_sec * 1000) + (time.tv_usec / 1000);


	long spent = end - start;
	printf("Loop took %ld ms\n", spent);
	/////////////////////////////



	return (0);
}

void	usage()
{
	ft_printf("Usage : ./mod1 ./path/to/map/map.mod1 [scenario]\n");
	ft_printf("Scenarios:\n");
	ft_printf("0: Wave\n");
	ft_printf("1: Rain\n");
	ft_printf("2: Rising water\n");
	exit(2);
}

int		main(int argc, char **argv)
{
	t_stuffs	stuffs;
	t_stuffs	water;

	if (argc != 3)
		usage();
	if (argv[2][0] == '0')
		stuffs.scenario = WAVE;
	else if (argv[2][0] == '1')
		stuffs.scenario = RAIN;
	else if (argv[2][0] == '2')
		stuffs.scenario = RISING_WATER;
	else
		usage();
	stuffs.water = &water;
	stuffs.water_lvl = 0;
	water.water = 0;
	if (init(&stuffs, argv[1]))
		return (1);
	water.co = stuffs.co;
	water.win = stuffs.win;
	if (init(&water, argv[1]))
		return (1);
	mlx_put_image_to_window(stuffs.co, stuffs.win, stuffs.img.ptr, 0, 0);
	mlx_loop_hook(stuffs.co, water_loop, &stuffs);
	mlx_key_hook(stuffs.win, hook, &stuffs);
	mlx_loop(stuffs.co);
	return (0);
}
