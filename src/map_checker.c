/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 00:00:00 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 00:00:00 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

static bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	check_mapcontent_sanity(t_core *cub)
{
	size_t	y;
	size_t	x;
	char	*line;
	int		player_count;

	if (cub->map.size.y == 0 || !cub->map.grid || !cub->map.grid[0])
		error_print("Invalid map content", MAP_CONTENT_ERROR, cub);
	player_count = 0;
	y = 0;
	while (y < (size_t)cub->map.size.y)
	{
		line = cub->map.grid[y];
		if ((int)ft_strlen(line) > cub->map.size.x)
			cub->map.size.x = (int)ft_strlen(line);
		x = 0;
		while (line[x])
		{
			if (!is_valid_map_char(line[x]))
				error_print("Invalid character in map", MAP_CONTENT_ERROR, cub);
			if (is_player_char(line[x]))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error_print("Invalid player settings", MAP_CONTENT_ERROR, cub);
}
