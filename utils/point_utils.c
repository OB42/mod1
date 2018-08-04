/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:54:23 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/15 05:54:25 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

t_p2d	f2d_to_p2d(t_f2d floatpoint)
{
	t_p2d ret;

	ret.x = (int)floatpoint.x;
	ret.y = (int)floatpoint.y;
	ret.elev = floatpoint.elev;
	return (ret);
}
