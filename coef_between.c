#include "mod1.h"

t_between get_cor(t_stuffs *stuffs, t_p2d coords, char dir)
{
	t_between c;

	c.from = (coords.y - 1) * (stuffs->linelen);
	c.to = (coords.y) * (stuffs->linelen);
	c.other = (coords.x - 1) * (stuffs->linelen);
	if (dir == 'S')
	{
		c.from = (coords.x - 1) * (stuffs->linelen);
		c.to = (coords.x) * (stuffs->linelen);
		c.other = (coords.y) * (stuffs->linelen);
	}
	if (dir == 'N')
	{
		c.from = (coords.x - 1) * (stuffs->linelen);
		c.to = (coords.x) * (stuffs->linelen);
		c.other = (coords.y - 1) * (stuffs->linelen);
	}
	if (dir == 'W')
	{
		c.from = (coords.y - 1) * (stuffs->linelen);
		c.to = (coords.y) * (stuffs->linelen);
		c.other = (coords.x) * (stuffs->linelen);
	}
		return (c);
}

int	coef_vertical(t_stuffs *stuffs, t_p2d coords, char dir, int water_lvl)
{
	t_between c;
	int cpt;

	c =  get_cor(stuffs, coords, dir);
	cpt = 0;
		if ((c.other < (stuffs->size_y * stuffs->linelen))
		&& (c.to < (stuffs->size_x * stuffs->linelen)))
		{
			while (c.from < c.to)
			{
				if (stuffs->bigmap[c.from][c.other].elev < water_lvl)
					cpt++;
				c.from++;
			}
		}
	return (cpt);
}


float	coef_horiz(t_stuffs *stuffs, t_p2d coords, char dir, int water_lvl)
{
	t_between c;
	int cpt;

	c =  get_cor(stuffs, coords, dir);
	cpt = 0;
	if ((c.other < (stuffs->size_x * stuffs->linelen))
	&& (c.to < (stuffs->size_y * stuffs->linelen)))
		{
			while (c.from < c.to)
			{
				if (stuffs->bigmap[c.other][c.from].elev < water_lvl)
					cpt++;
				c.from++;
			}
		}
	return (cpt);
}

float coef_between(t_stuffs *stuffs, t_p2d coords, char dir, int water_lvl)
{
	int cpt;

	if (dir == 'N' || dir == 'S')
		cpt = coef_vertical(stuffs, coords, dir, water_lvl);
	else
		cpt = coef_horiz(stuffs, coords, dir, water_lvl);
	return ((float)cpt)/(stuffs->linelen);
}
