/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:51:42 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/15 06:29:54 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

void	redraw(t_stuffs *stu)
{
	//opti
	////////////////////////////
	struct timeval time;
	gettimeofday(&time, NULL);
	long start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////


	clear(stu);


	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	long end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	long spent = end - start;
	printf("\t clear took %ld ms\n", spent);
	/////////////////////////////

	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////



	set_dots(stu);



	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	spent = end - start;
	printf("\t set_dots took %ld ms\n", spent);
	/////////////////////////////


	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////



	connect_dots(stu);


	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	spent = end - start;
	printf("\t connect_dots took %ld ms\n", spent);
	/////////////////////////////

	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////





	mlx_put_image_to_window(stu->co, stu->win, stu->img.ptr, 0, 0);

	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	spent = end - start;
	printf("\t img to win took %ld ms\n", spent);
	/////////////////////////////


}


void	redraw_water(t_stuffs *stu)
{
	//opti
	////////////////////////////
	struct timeval time;
	gettimeofday(&time, NULL);
	long start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////


	//clear(stu);


	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	long end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	long spent = end - start;
	printf("\t clear took %ld ms\n", spent);
	/////////////////////////////

	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////



	set_dots(stu);



	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	spent = end - start;
	printf("\t set_dots took %ld ms\n", spent);
	/////////////////////////////


	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////



	connect_water_dots(stu);


	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	spent = end - start;
	printf("\t connect_dots took %ld ms\n", spent);
	/////////////////////////////

	//opti
	////////////////////////////
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	///////////////////////////





	mlx_put_image_to_window(stu->co, stu->win, stu->img.ptr, 0, 0);

	//opti
	//////////////////////////////
	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	spent = end - start;
	printf("\t img to win took %ld ms\n", spent);
	/////////////////////////////


}



void	dirty_water_rising(t_stuffs *stuffs, int level)
{
	int e;
	int w;

	e = 0;
	while (e < ((stuffs->size_x) * stuffs->linelen))
	{
		w = 0;
		while ((w < (stuffs->size_y) * stuffs->linelen))
		{
			stuffs->water->bigmap[e][w].elev += level;
			stuffs->water->bigmap[e][w].y -= level * stuffs->coef;
			w++;
		}
		e++;
	}
	e = 1;
	while (e <= stuffs->size_x)
	{
		w = 1;
		while (w <= stuffs->size_y)
		{
			stuffs->water->map[e][w].elev += level;
			stuffs->water->map[e][w].y -= level * stuffs->coef;
			stuffs->water->elevs[e][w] += level;
			w++;
		}
		e++;
	}
}
void	free_stuffs(t_stuffs *stuffs)
{
	int e;

	e = 1;
	while (e <= stuffs->size_x)
	{
		free((stuffs->map)[e]);
		free((stuffs->elevs)[e]);
		e++;
	}
	free(stuffs->map);
	free(stuffs->elevs);
}

int		hook(int keycode, void *stuffs)
{
	if (keycode == 53)
	{
		free_stuffs(stuffs);
		exit(0);
	}
	if (keycode == 0x7C)
		((t_stuffs*)stuffs)->img.x += POS_INCREMENT;
	else if (keycode == 0x7B)
		((t_stuffs*)stuffs)->img.x -= POS_INCREMENT;
	else if (keycode == 0x7D)
		((t_stuffs*)stuffs)->img.y += POS_INCREMENT;
	else if (keycode == 0x7E)
		((t_stuffs*)stuffs)->img.y -= POS_INCREMENT;
	else if (keycode == 0x45)
	{
		((t_stuffs*)stuffs)->raining_intensity -= RAIN_INCREMENT;
		if (((t_stuffs*)stuffs)->raining_intensity < RAIN_INCREMENT)
			((t_stuffs*)stuffs)->raining_intensity = RAIN_INCREMENT;
	}
	else if (keycode == 0x4E)
	{
		((t_stuffs*)stuffs)->raining_intensity += RAIN_INCREMENT;
		if (((t_stuffs*)stuffs)->raining_intensity > 100)
			((t_stuffs*)stuffs)->raining_intensity = 100;
	}
	return (0);
}

int		exit_msg(int ret_code)
{
	if (!ret_code)
		return (0);
	else if (ret_code == -1)
		ft_printf(" -> File not found, aborting.\n");
	else if (ret_code == -2)
		ft_printf(" -> File exist but is incorrect in some way.\n");
	else if (ret_code > 0)
		ft_printf(" -> Incorrect line (%d) found in file, abort.\n", ret_code);
	return (1);
}
