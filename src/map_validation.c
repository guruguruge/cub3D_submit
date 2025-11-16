/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 00:00:00 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 00:00:00 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	in_targets(char c, char *targets)
{
	size_t	i;

	i = 0;
	while (targets[i])
	{
		if (c == targets[i])
			return (1);
		i++;
	}
	return (0);
}

void	fill(char **tab, t_point size, t_point cur, char *targets)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| !in_targets(tab[cur.y][cur.x], targets))
		return ;
	tab[cur.y][cur.x] = 'F';
	fill(tab, size, (t_point){cur.x - 1, cur.y}, targets);
	fill(tab, size, (t_point){cur.x + 1, cur.y}, targets);
	fill(tab, size, (t_point){cur.x, cur.y - 1}, targets);
	fill(tab, size, (t_point){cur.x, cur.y + 1}, targets);
}

char	**create_padded_map_copy(t_core *cub, t_point map_size,
		t_point *tmp_size)
{
	char	**tmp;
	int		y;
	int		x;
	int		len;

	tmp_size->x = map_size.x + 2;
	tmp_size->y = map_size.y + 2;
	tmp = malloc(sizeof(char *) * tmp_size->y);
	if (!tmp)
		error_print("malloc fail", MALLOC_ERROR, cub);
	y = 0;
	while (y < tmp_size->y)
	{
		tmp[y] = malloc((tmp_size->x + 1) * sizeof(char));
		if (!tmp[y])
		{
			free_args_fail(tmp, y);
			error_print("malloc fail", MALLOC_ERROR, cub);
		}
		x = 0;
		while (x < tmp_size->x)
		{
			tmp[y][x] = ' ';
			x++;
		}
		tmp[y][tmp_size->x] = '\0';
		y++;
	}
	y = 0;
	while (y < map_size.y)
	{
		len = (int)ft_strlen(cub->map.grid[y]);
		x = 0;
		while (x < len && x < map_size.x)
		{
			tmp[y + 1][x + 1] = cub->map.grid[y][x];
			x++;
		}
		y++;
	}
	return (tmp);
}

void	check_map_enclosed(t_core *cub, char **tmp, t_point map_size,
		t_point tmp_size)
{
	t_point	size;
	t_point	start;
	int		y;
	int		x;
	int		len;
	char	orig;

	size.x = tmp_size.x;
	size.y = tmp_size.y;
	start.x = 0;
	start.y = 0;
	fill(tmp, size, start, " 0NSEW");
	y = 0;
	while (y < map_size.y)
	{
		len = (int)ft_strlen(cub->map.grid[y]);
		x = 0;
		while (x < len && x < map_size.x)
		{
			orig = cub->map.grid[y][x];
			if ((orig == '0' || orig == 'N' || orig == 'S' || orig == 'E'
					|| orig == 'W') && tmp[y + 1][x + 1] == 'F')
			{
				free_args_fail(tmp, tmp_size.y);
				error_print("Map not enclosed", MAP_CONTENT_ERROR, cub);
			}
			if (orig == ' ' && tmp[y + 1][x + 1] != 'F')
			{
				free_args_fail(tmp, tmp_size.y);
				error_print("Map not enclosed", MAP_CONTENT_ERROR, cub);
			}
			x++;
		}
		y++;
	}
}
