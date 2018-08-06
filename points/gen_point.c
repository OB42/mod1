/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 05:50:59 by pcluchet          #+#    #+#             */
/*   Updated: 2017/02/17 07:54:28 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

t_p2d		gen_point(t_p2d p1, t_p2d p2, float whereami)
{
	float coef;
	float sinuscorrect;
	int elevnow;
	float sinelev;
	t_p2d ret;

	coef = whereami;
	sinuscorrect = -(M_PI/2.0);
	elevnow = ((float)p2.elev - (float)p1.elev);
	if (p2.elev < p1.elev)
	{
		elevnow = ((float)p1.elev - (float)p2.elev);
		coef = 1.0 - whereami;
		sinuscorrect = M_PI/2.0;
	}
	sinelev =  sin(whereami * M_PI +  sinuscorrect)+1.0;
	ret = p1;
	ret.y -=  fabs(sinelev/2.0 * ((float)elevnow));
	if (p1.elev != 0 &&  p2.elev != 0)
		ret.y -=  (p2.elev > p1.elev) ? fabsf(p1.elev) : fabsf(p2.elev);
	ret.elev = abs(p1.y - ret.y);
	return (ret);
}
