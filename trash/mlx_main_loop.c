/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-12 21:47:42 by sguruge           #+#    #+#             */
/*   Updated: 2025-08-12 21:47:42 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	get_radian(double deg)
{
	return (PI * (deg / 180));
}

void	get_theata_x(t_core *cub)
{
	int		i;
	double	fov;
	double	p_radian;

	i = 0;
	fov = cub->conf.fov;
	p_radian = get_radian(cub->player1.deg);
	while (i < WIN_X)
	{
		cub->conf.theata_x[i] = p_radian - fov / 2 + (double)(i / WIN_X) * fov;
		i++;
	}
}

double	init_side_dist(int pos, float pos_f, bool sign, double d_dis)
{

	if (sign)
		return ((pos + 1.0 - pos_f) * d_dis);
	else
		return ((pos_f - pos) * d_dis);
}

void	first_quad_dda(t_core *cub, t_point plr, int idx)
{
	cub->conf.side[idx] = -1;
	cub->conf.side_dist[idx].x = init_side_dist(plr.x, cub->player1.pos_f.x,
			true, cub->conf.d_distance[idx].x);
	cub->conf.side_dist[idx].y = init_side_dist(plr.y, cub->player1.pos_f.y,
			true, cub->conf.d_distance[idx].y);
	while (cub->conf.side[idx] == -1)
	{
		if (cub->conf.side_dist[idx].x < cub->conf.side_dist[idx].y)
		{
			cub->conf.side_dist[idx].x += cub->conf.d_distance[idx].x;
			cub->conf.ray_pos[idx].x += 1;
			cub->conf.side[idx] = VERTICAL;
		}
		else
		{
			cub->conf.side_dist[idx].y += cub->conf.d_distance[idx].y;
			cub->conf.ray_pos[idx].y += 1;
			cub->conf.side[idx] = HORIZONAL;
		}
		if (cub->map.grid[cub->conf.ray_pos[idx].y][cub->conf.ray_pos[idx].x] == '1')
			break ;
	}
}

void	second_quad_dda(t_core *cub, t_point plr, int idx)
{
	cub->conf.side[idx] = -1;
	cub->conf.side_dist[idx].x = init_side_dist(plr.x, cub->player1.pos_f.x,
			false, cub->conf.d_distance[idx].x);
	cub->conf.side_dist[idx].y = init_side_dist(plr.y, cub->player1.pos_f.y,
			true, cub->conf.d_distance[idx].y);
	while (cub->conf.side[idx] == -1)
	{
		if (cub->conf.side_dist[idx].x < cub->conf.side_dist[idx].y)
		{
			cub->conf.side_dist[idx].x += cub->conf.d_distance[idx].x;
			cub->conf.ray_pos[idx].x -= 1;
			cub->conf.side[idx] = VERTICAL;
		}
		else
		{
			cub->conf.side_dist[idx].y += cub->conf.d_distance[idx].y;
			cub->conf.ray_pos[idx].y += 1;
			cub->conf.side[idx] = HORIZONAL;
		}
		if (cub->map.grid[cub->conf.ray_pos[idx].y][cub->conf.ray_pos[idx].x] == '1')
			break ;
	}
}

void	third_quad_dda(t_core *cub, t_point plr, int idx)
{
	cub->conf.side[idx] = -1;
	cub->conf.side_dist[idx].x = init_side_dist(plr.x, cub->player1.pos_f.x,
			false, cub->conf.d_distance[idx].x);
	cub->conf.side_dist[idx].y = init_side_dist(plr.y, cub->player1.pos_f.y,
			false, cub->conf.d_distance[idx].y);
	while (cub->conf.side[idx] == -1)
	{
		if (cub->conf.side_dist[idx].x < cub->conf.side_dist[idx].y)
		{
			cub->conf.side_dist[idx].x += cub->conf.d_distance[idx].x;
			cub->conf.ray_pos[idx].x -= 1;
			cub->conf.side[idx] = VERTICAL;
		}
		else
		{
			cub->conf.side_dist[idx].y += cub->conf.d_distance[idx].y;
			cub->conf.ray_pos[idx].y -= 1;
			cub->conf.side[idx] = HORIZONAL;
		}
		if (cub->map.grid[cub->conf.ray_pos[idx].y][cub->conf.ray_pos[idx].x] == '1')
			break ;
	}
}

void	fourth_quad_dda(t_core *cub, t_point plr, int idx)
{
	cub->conf.side[idx] = -1;
	cub->conf.side_dist[idx].x = init_side_dist(plr.x, cub->player1.pos_f.x,
			true, cub->conf.d_distance[idx].x);
	cub->conf.side_dist[idx].y = init_side_dist(plr.y, cub->player1.pos_f.y,
			false, cub->conf.d_distance[idx].y);
	while (cub->conf.side[idx] == -1)
	{
		if (cub->conf.side_dist[idx].x < cub->conf.side_dist[idx].y)
		{
			cub->conf.side_dist[idx].x += cub->conf.d_distance[idx].x;
			cub->conf.ray_pos[idx].x += 1;
			cub->conf.side[idx] = VERTICAL;
		}
		else
		{
			cub->conf.side_dist[idx].y += cub->conf.d_distance[idx].y;
			cub->conf.ray_pos[idx].y -= 1;
			cub->conf.side[idx] = HORIZONAL;
		}
		if (cub->map.grid[cub->conf.ray_pos[idx].y][cub->conf.ray_pos[idx].x] == '1')
			break ;
	}
}

void	get_d_distance(t_core *cub)
{
	int	i;

	i = 0;
	while (i < WIN_X)
	{
		if (cos(cub->conf.theata_x[i]) < 1e-9)
			cub->conf.d_distance[i].x = (int)1e+30;
		else
			cub->conf.d_distance[i].x = fabs(1 / cos(cub->conf.theata_x[i]));
		if (sin(cub->conf.theata_x[i]) < 1e-9)
			cub->conf.d_distance[i].y = (int)1e+30;
		else
			cub->conf.d_distance[i].y = fabs(1 / sin(cub->conf.theata_x[i]));
		i++;
	}
}

void	dda_algorithm(t_core *cub)
{
	int		i;
	t_point	player;

	player.x = (int)cub->player1.pos_f.x;
	player.y = (int)cub->player1.pos_f.y;
	i = 0;
	while (i < WIN_X)
	{
		cub->conf.ray_pos[i] = player;
		if (cos(cub->conf.theata_x[i]) > 0 && sin(cub->conf.theata_x[i]) > 0)
			first_quad_dda(cub, player, i);
		else if (cos(cub->conf.theata_x[i]) < 0
			&& sin(cub->conf.theata_x[i]) > 0)
			second_quad_dda(cub, player, i);
		else if (cos(cub->conf.theata_x[i]) < 0
			&& sin(cub->conf.theata_x[i]) < 0)
			third_quad_dda(cub, player, i);
		else if (cos(cub->conf.theata_x[i]) > 0
			&& sin(cub->conf.theata_x[i]) < 0)
			fourth_quad_dda(cub, player, i);
		cub->conf.ray_pos[i] = player;
		i++;
	}
}

void	correct_distance(t_core *cub)
{
	int		i;
	int		step_y;
	int		step_x;
	double	distance;
	double	plr_radian;

	i = 0;
	while (i < WIN_X)
	{
		if (cos(cub->conf.theata_x[i]) > 0)
			step_x = 1;
		else
			step_x = -1;
		if (sin(cub->conf.theata_x[i]) > 0)
			step_y = 1;
		else
			step_y = -1;
		if (cub->conf.side[i] == HORIZONAL)
		{
			distance = (cub->conf.ray_pos[i].y - cub->player1.pos_f.y + (1 - step_y) / 2) / sin(cub->conf.theata_x[i]);
			plr_radian = get_radian(cub->player1.deg);
			cub->conf.corr_distance[i] = fabs(distance) * cos(cub->conf.theata_x[i]  - plr_radian);
		}
		else if (cub->conf.side[i] == VERTICAL)
		{
			distance = (cub->conf.ray_pos[i].x - cub->player1.pos_f.x + (1
						- step_x) / 2) / cos(cub->conf.theata_x[i]);
			plr_radian = get_radian(cub->player1.deg);
			cub->conf.corr_distance[i] = fabs(distance) * cos(cub->conf.theata_x[i] - plr_radian);
		}
		i++;
	}
}

void get_wall_height(t_core *cub)
{
	int i = 0;

	while (i < WIN_X)
	{
		cub->conf.wall_h[i] = (double)(H_WALL * D) / cub->conf.corr_distance[i];
		i++;
	}
}

void pixel_put(t_core *cub,int x, int y, int rgb)
{
	int pixel = y * cub->graphic.size_line + x * (cub->graphic.bits_p_pixel / 8);
	*(int *)(cub->graphic.data_addr + pixel) = rgb;
}

void    draw_wall_slice(t_core *cub,int draw_start, int draw_end, int x)
{
    int y;
    int wall_height;


    wall_height = cub->conf.wall_h[x];
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= WIN_Y)
        draw_end = WIN_Y - 1;
    y = 0;
    while (y < draw_start)
    {
        pixel_put(cub, x, y, cub->graphic.surface[C].rgb);
        y++;
    }
    y = draw_start;
    while (y <= draw_end)
    {
        // テクスチャマッピングを行う場合は、ここでテクスチャの色を取得します。
        pixel_put(cub, x, y, create_rgb(0,0,0));
        y++;
    }
    y = draw_end + 1;
    while (y < WIN_Y)
    {
        pixel_put(cub, x, y,  cub->graphic.surface[F].rgb);
        y++;
    }
}

void put_picture(t_core *cub)
{
	int i = 0;

	if(cub->graphic.frame)
		mlx_destroy_image(cub->mlx.p , cub->graphic.frame);
	cub->graphic.frame = mlx_new_image(cub->mlx.p, WIN_X,WIN_Y);
	if(cub->graphic.frame == NULL)
	{
		error_print("new img fail", MALLOC_ERROR, cub);
	}
	cub->graphic.data_addr = mlx_get_data_addr(cub->graphic.frame, &cub->graphic.bits_p_pixel,
			&cub->graphic.size_line, &cub->graphic.endian);
	if(cub->graphic.data_addr == NULL)
	{
		error_print("data adrr fail", MALLOC_ERROR, cub);
	}
	while (i < WIN_X)
	{
		int drw_start = (WIN_Y/2) - (int)(cub->conf.wall_h[i] / 2);
		int drw_end = (WIN_Y/2) + (int)(cub->conf.wall_h[i] / 2);
	
		draw_wall_slice(cub, drw_start,drw_end,i);
		i++;
	}
	mlx_put_image_to_window(cub->mlx.p, cub->mlx.win,cub->graphic.frame , 0, 0);
}

// θxは画面上の描画の横の角度 θpは地図上のプレイヤーの角度

int	render(void *cub_v)
{
	t_core	*cub;

	cub = (t_core *)cub_v;
	// render surface
	// mlx_put_image_to_window(cub->mlx.p, cub->mlx.win,
	// 	cub->graphic.surface[C].ptr, 0, 0);
	// mlx_put_image_to_window(cub->mlx.p, cub->mlx.win,
	// 	cub->graphic.surface[F].ptr, 0, WIN_Y / 2);
	// render walls
	render_wall(cub);
	return (0);
}

void	main_loop(t_core *cub)
{
	void	*cub_v;

	cub_v = (void *)cub;
	// mlx_hook();
	mlx_loop_hook(cub->mlx.p, *render, cub_v);
	mlx_loop(cub->mlx.p);
}
