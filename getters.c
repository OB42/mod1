/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 06:11:17 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 11:07:55 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

int	gory(t_stuffs *stuffs, int index)
{
	if (stuffs->viewpoint == 2 || stuffs->viewpoint == 4)
		index = stuffs->size_y - index + 1;
	return (index);
}

int	gorx(t_stuffs *stuffs, int index)
{
	if (stuffs->viewpoint == 3 || stuffs->viewpoint == 4)
		index = stuffs->size_x - index + 1;
	return (index);
}
