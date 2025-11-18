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
		error_print("Malloc fail", MALLOC_ERROR, cub);
	y = 0;
	while (y < tmp_size->y)
	{
		tmp[y] = malloc((tmp_size->x + 1) * sizeof(char));
		if (!tmp[y])
		{
			free_args_fail(tmp, y);
			error_print("Malloc fail", MALLOC_ERROR, cub);
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

static bool	is_surrounded_by_walls(char **grid, int max_y, int max_x, int y,
		int x)
{
	int		len_up;
	int		len_down;
	char	up_char;
	char	down_char;

	/* 上下チェック（存在チェック） */
	if (y <= 0 || y >= max_y - 1)
		return (false);
	/* 左右チェック */
	if (x <= 0 || x >= max_x - 1)
		return (false);
	/* 上の行が存在し、その行の長さが x より大きいか確認 */
	len_up = (int)ft_strlen(grid[y - 1]);
	/* x が行の長さを超えていたら、その位置は ' '（パディング）扱い */
	up_char = (x >= len_up) ? ' ' : grid[y - 1][x];
	if (up_char == ' ')
		return (false);
	/* 下の行が存在し、その行の長さが x より大きいか確認 */
	len_down = (int)ft_strlen(grid[y + 1]);
	down_char = (x >= len_down) ? ' ' : grid[y + 1][x];
	if (down_char == ' ')
		return (false);
	/* 左右チェック */
	if (grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ')
		return (false);
	return (true);
}

void	check_mapstructure_sanity(t_core *cub)
{
	t_point	map_size;
	int		y;
	int		x;
	int		len;
	char	orig;

	map_size.x = cub->map.size.x;
	map_size.y = cub->map.size.y;
	if (map_size.x <= 0 || map_size.y <= 0)
		error_print("Invalid map structure", MAP_CONTENT_ERROR, cub);
	/* 四方向チェック：各 '0' / プレイヤー文字の上下左右が壁で保護されているか */
	y = 0;
	while (y < map_size.y)
	{
		len = (int)ft_strlen(cub->map.grid[y]);
		x = 0;
		while (x < len && x < map_size.x)
		{
			orig = cub->map.grid[y][x];
			if (orig == '0' || orig == 'N' || orig == 'S' || orig == 'E'
				|| orig == 'W')
			{
				if (!is_surrounded_by_walls(cub->map.grid, map_size.y,
						map_size.x, y, x))
					error_print("Map not enclosed", MAP_CONTENT_ERROR, cub);
			}
			x++;
		}
		y++;
	}
}
