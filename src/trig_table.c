#include "../inc/cub3d.h"

void	init_atan_table(t_core *cub)
{
	int		idx;
	double	ratio;

	ratio = 0.0;
	idx = 0;
	while (ratio < 10.0)
	{
		cub->trig_table.atan_table[idx] = atan(ratio);
		idx++;
		ratio += 0.001;
	}
}

double	fast_atan2(double y, double x, t_core cub)
{
	double	ratio;
	double	atan;
	int		idx;

	if (x < 1e-9)
    {
        if(y > 0)
            return(PI / 2);
        else if(y < 0)
            return(-1 * PI / 2);
    }
	else
		ratio = fabs(y / x);
	idx = (int)(ratio * 1000);
	if (idx >= RATIO_PRECISION)
		idx = RATIO_PRECISION - 1;
	atan = cub.trig_table.atan_table[idx];
	if (x < 0)
		atan = PI - atan;
	if (y < 0)
		atan = -atan;
	return (atan);
}

void	init_trig_table(t_core *cub)
{
	int		i;
	double	radian;

	i = 0;
	radian = 0;
	while (i < RADIAN_PRECISION)
	{
		radian = (double)i / 1000.0;
		cub->trig_table.cos_table[i] = cos(radian);
		cub->trig_table.sin_table[i] = sin(radian);
		i++;
	}
	init_atan_table(cub);
}

double	fast_cos(double radian, t_core cub)
{
	int	idx;

	radian = fmod(radian, PI * 2);
	idx = (int)(radian * 1000) % RADIAN_PRECISION;
	return (cub.trig_table.cos_table[idx]);
}

double	fast_sin(double radian, t_core cub)
{
	int	idx;

	radian = fmod(radian, PI * 2);
	idx = (int)(radian * 1000) % RADIAN_PRECISION;
	return (cub.trig_table.sin_table[idx]);
}
