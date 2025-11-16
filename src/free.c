/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-03 22:35:19 by sguruge           #+#    #+#             */
/*   Updated: 2025-07-03 22:35:19 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_all(t_core *cub);
void	free_args(char **args);
void	free_args_fail(char **args, int size);

void	free_all(t_core *cub)
{
	(void)cub;
	// int	i;
	// if (!cub)
	// 	return ;
	// /* destroy images if mlx is initialized */
	// if (cub->graphic.wall)
	// {
	// 	i = 0;
	// 	while (i < 4)
	// 	{
	// 		if (cub->graphic.wall[i].ptr && cub->mlx.p)
	// 			mlx_destroy_image(cub->mlx.p, cub->graphic.wall[i].ptr);
	// 		if (cub->graphic.wall[i].path)
	// 			free(cub->graphic.wall[i].path);
	// 		i++;
	// 	}
	// 	free(cub->graphic.wall);
	// }
	// if (cub->graphic.surface)
	// 	free(cub->graphic.surface);
	// if (cub->graphic.frame && cub->mlx.p)
	// 	mlx_destroy_image(cub->mlx.p, cub->graphic.frame);
	// if (cub->mlx.win && cub->mlx.p)
	// 	mlx_destroy_window(cub->mlx.p, cub->mlx.win);
	// if (cub->raw_input)
	// 	free_args(cub->raw_input);
	// if (cub->parsed_input)
	// 	free_args(cub->parsed_input);
	// if (cub->map.grid)
	// 	free_args(cub->map.grid);
	// free(cub);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_args_fail(char **args, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(args[i]);
		i++;
	}
	free(args);
}
