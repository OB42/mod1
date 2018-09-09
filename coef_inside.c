#include "mod1.h"



float coef_inside(t_stuffs *stuffs, t_p2d coords, t_p2d fromto, int water_lvl)
{
	t_p2d from;
	t_inside coefs;
	int cpt;
	int i;

	cpt = 0;
	if (fromto.x == 'N')
	{
		if (fromto.y == 'E')		
		coefs = (t_inside){.fromx = 1, .fromy = 1, .loopx = 1, .loopy = 1 };
		else if (fromto.y == 'W')
		coefs = (t_inside){.fromx = 0, .fromy = 1, .loopx = -1, .loopy = 1 };
	}
	if (fromto.x == 'W')
	{
		if (fromto.y == 'S')	
		coefs = (t_inside){.fromx = 0, .fromy = 0, .loopx = -1, .loopy = -1 };
		if (fromto.y == 'N')		
		coefs = (t_inside){.fromx = 0, .fromy = 1, .loopx = -1, .loopy = 1 };
	}
	if (fromto.x == 'E')
	{
		if (fromto.y == 'S')		
		coefs = (t_inside){.fromx = 1, .fromy = 0, .loopx = 1, .loopy = -1 };
		if (fromto.y == 'N')		
		coefs = (t_inside){.fromx = 1, .fromy = 1, .loopx = 1, .loopy = 1 };
	}

	if (fromto.x == 'S')
	{
		if (fromto.y == 'E')		
		coefs = (t_inside){.fromx = 1, .fromy = 0, .loopx = 1, .loopy = -1 };
		else if (fromto.y == 'W')
		coefs = (t_inside){.fromx = 0, .fromy = 0, .loopx = -1, .loopy = -1 };
	}

	from.x = (coords.x - coefs.fromx) * stuffs->linelen;
	from.y = (coords.y - coefs.fromy) * stuffs->linelen;

	i = 0;
	while ( (i < (stuffs->linelen / 2)) &&
	(from.x + (i * coefs.loopx)) < (stuffs->size_x * stuffs->linelen)  &&  
	(from.y + (i * coefs.loopy)) < (stuffs->size_y * stuffs->linelen)  
	      )
	{
		if (stuffs->bigmap[from.x + (i * coefs.loopx)][from.y + (i * coefs.loopy)].elev < water_lvl)
			cpt++;
		i++;
	}

	float ret = ( ((float)cpt)/ (stuffs->linelen / 2.0) - 0.0);
	if (ret < 0)
		ret = 0.0;
	if (ret > 0.12)
		ret = 1.0;

	printf("coef : %f\n",  ret  );
	return (ret);
}

