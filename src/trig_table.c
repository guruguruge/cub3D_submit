/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:21:53 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:21:53 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_trig_table(t_core *cub)
{
	int		i;
	double	radian;

	i = 0;
	radian = 0;
	cub->trig_table.sin_table = malloc(sizeof(double) * RADIAN_PRECISION);
	if (!cub->trig_table.sin_table)
		error_print("Malloc fail", MALLOC_ERROR, cub);
	cub->trig_table.cos_table = malloc(sizeof(double) * RADIAN_PRECISION);
	if (!cub->trig_table.cos_table)
		error_print("Malloc fail", MALLOC_ERROR, cub);
	while (i < RADIAN_PRECISION)
	{
		radian = (double)i / 1000.0;
		cub->trig_table.cos_table[i] = cos(radian);
		cub->trig_table.sin_table[i] = sin(radian);
		i++;
	}
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
