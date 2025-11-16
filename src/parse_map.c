/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:21:25 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:21:25 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	take_off_newline(char *map_line)
{
	size_t	len;

	len = ft_strlen(map_line);
	if (map_line[len - 1] == '\n')
	{
		map_line[len - 1] = '\0';
	}
}

void	parse_map(t_core *cub, char *map_line)
{
	if (is_emptyline(map_line))
	{
		if (cub->map.size.y == 0)
			return ;
		else
			error_print("Invalid map structure", CONTENT_ERROR, cub);
	}
	cub->map.grid[cub->map.size.y] = ft_strdup(map_line);
	if (!cub->map.grid[cub->map.size.y])
	{
		if (cub->map.grid)
			free_args_fail(cub->map.grid, cub->map.size.y);
		error_print("malloc fail", MALLOC_ERROR, cub);
	}
	take_off_newline(cub->map.grid[cub->map.size.y]);
	cub->map.size.y++;
}

void	check_mapstructure_sanity(t_core *cub)
{
	t_point	map_size;
	t_point	tmp_size;
	char	**tmp;

	map_size.x = cub->map.size.x;
	map_size.y = cub->map.size.y;
	if (map_size.x <= 0 || map_size.y <= 0)
		error_print("Invalid map structure", MAP_CONTENT_ERROR, cub);
	tmp = create_padded_map_copy(cub, map_size, &tmp_size);
	check_map_enclosed(cub, tmp, map_size, tmp_size);
	free_args_fail(tmp, tmp_size.y);
}
