/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:20:31 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:20:31 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calc_delta_time(t_core *cub)
{
	struct timeval	cur_time;
	long			sec_diff;
	long			usec_diff;

	gettimeofday(&cur_time, NULL);
	sec_diff = cur_time.tv_sec - cub->last_update_time.tv_sec;
	usec_diff = cur_time.tv_usec - cub->last_update_time.tv_usec;
	cub->d_time = (double)sec_diff + ((double)usec_diff / 1000000.0);
	cub->last_update_time = cur_time;
}
