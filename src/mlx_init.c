/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:21:01 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:21:01 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_wall_img(t_core *cub);
void	init_mlx(t_core *cub);

void	init_wall_img_addr(t_wall *wall_img)
{
	wall_img->data_addr = mlx_get_data_addr(wall_img->ptr, &wall_img->bpp,
			&wall_img->size_line, &wall_img->endian);
}

void	get_wall_img(t_core *cub)
{
	char	*path;
	int		i;
	int		n;

	n = 64;
	path = cub->graphic.wall[NO].path;
	cub->graphic.wall[NO].ptr = mlx_xpm_file_to_image(cub->mlx.p, path, &n, &n);
	path = cub->graphic.wall[SO].path;
	cub->graphic.wall[SO].ptr = mlx_xpm_file_to_image(cub->mlx.p, path, &n, &n);
	path = cub->graphic.wall[WE].path;
	cub->graphic.wall[WE].ptr = mlx_xpm_file_to_image(cub->mlx.p, path, &n, &n);
	path = cub->graphic.wall[EA].path;
	cub->graphic.wall[EA].ptr = mlx_xpm_file_to_image(cub->mlx.p, path, &n, &n);
	if (!cub->graphic.wall[NO].ptr || !cub->graphic.wall[SO].ptr
		|| !cub->graphic.wall[EA].ptr || !cub->graphic.wall[WE].ptr)
		error_print("Invalid image path", CONTENT_ERROR, cub);
	i = 0;
	while (i <= EA)
	{
		init_wall_img_addr(&cub->graphic.wall[i]);
		i++;
	}
}

int	is_targets(char c, char *targets)
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

t_point	find_pos(t_core *cub, char *targets)
{
	t_point	p;

	p.y = 0;
	while (cub->map.grid[p.y])
	{
		p.x = 0;
		while (cub->map.grid[p.y][p.x])
		{
			if (is_targets(cub->map.grid[p.y][p.x], targets))
				return (p);
			p.x++;
		}
		p.y++;
	}
	return (p.x = -1, p.y = -1, p);
}

void	calculate_vectors(t_core *cub)
{
	double	view_length;
	double	player_rad;

	player_rad = cub->player1.deg_radian;
	cub->player1.dir_vec.x = fast_cos(player_rad, *cub);
	cub->player1.dir_vec.y = fast_sin(player_rad, *cub);
	view_length = tan(cub->conf.fov / 2);
	view_length = fast_cos(cub->conf.fov / 2, *cub) / fast_sin(cub->conf.fov
			/ 2, *cub);
	cub->player1.plane_vec.x = -1 * cub->player1.dir_vec.y * view_length;
	cub->player1.plane_vec.y = cub->player1.dir_vec.x * view_length;
}

void	init_player_config(t_core *cub)
{
	char	**map;
	int		y;
	int		x;

	map = cub->map.grid;
	cub->player1.pos = find_pos(cub, "NSEW");
	y = cub->player1.pos.y;
	x = cub->player1.pos.x;
	cub->player1.pos_d.y = (double)(cub->player1.pos.y) + 0.5;
	cub->player1.pos_d.x = (double)(cub->player1.pos.x) + 0.5;
	if (map[y][x] == 'N')
		cub->player1.deg_radian = 1.5 * PI;
	else if (map[y][x] == 'S')
		cub->player1.deg_radian = 0.5 * PI;
	else if (map[y][x] == 'W')
		cub->player1.deg_radian = PI;
	else if (map[y][x] == 'E')
		cub->player1.deg_radian = 2 * PI;
	cub->conf.fov = get_radian(FOV);
	cub->player1.pitch = 0;
	calculate_vectors(cub);
}

void	init_mlx(t_core *cub)
{
	cub->mlx.p = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.p, WIN_X, WIN_Y, "cub3D");
	cub->graphic.frame = NULL;
	get_wall_img(cub);
	init_trig_table(cub);
	init_player_config(cub);
	gettimeofday(&cub->last_update_time, NULL);
}
