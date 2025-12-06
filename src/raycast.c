/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:21:48 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:21:48 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calc_delta_dist(t_core *cub)
{
	t_pointd	ray_direction;

	ray_direction = cub->conf.ray_dir;
	if (fabs(ray_direction.x) < 1e-9)
		cub->conf.delta_dist.x = 1e+30;
	else
		cub->conf.delta_dist.x = fabs(1 / ray_direction.x);
	if (fabs(ray_direction.y) < 1e-9)
		cub->conf.delta_dist.y = 1e+30;
	else
		cub->conf.delta_dist.y = fabs(1 / ray_direction.y);
}

void	calc_steps(t_core *cub)
{
	if (cub->conf.ray_dir.x >= 0)
		cub->conf.step.x = 1;
	else
		cub->conf.step.x = -1;
	if (cub->conf.ray_dir.y >= 0)
		cub->conf.step.y = 1;
	else
		cub->conf.step.y = -1;
}

void	calc_side_dist(t_core *cub)
{
	t_pointd	delta_dist;

	delta_dist = cub->conf.delta_dist;
	if (cub->conf.ray_dir.x >= 0)
		cub->conf.side_dist.x = (delta_dist.x * ((double)cub->conf.map.x + 1.0
					- cub->player1.pos_d.x));
	else
		cub->conf.side_dist.x = (delta_dist.x * (cub->player1.pos_d.x
					- (double)cub->conf.map.x));
	if (cub->conf.ray_dir.y >= 0)
		cub->conf.side_dist.y = (delta_dist.y * ((double)cub->conf.map.y + 1.0
					- cub->player1.pos_d.y));
	else
		cub->conf.side_dist.y = (delta_dist.y * (cub->player1.pos_d.y
					- (double)cub->conf.map.y));
}

void	loop_init_raycast(t_core *cub, int idx)
{
	cub->conf.camera_x = 2 * idx / (double)WIN_X - 1;
	cub->conf.ray_dir.x = cub->player1.dir_vec.x + cub->player1.plane_vec.x
		* cub->conf.camera_x;
	cub->conf.ray_dir.y = cub->player1.dir_vec.y + cub->player1.plane_vec.y
		* cub->conf.camera_x;
	cub->conf.map = cub->player1.pos;
	calc_delta_dist(cub);
	calc_steps(cub);
	calc_side_dist(cub);
}

void	calc_wall_line(t_core *cub, int idx)
{
	(void)idx;
	if (cub->conf.side == VERTICAL)
		cub->conf.corr_distance = cub->conf.side_dist.x
			- cub->conf.delta_dist.x;
	else
		cub->conf.corr_distance = cub->conf.side_dist.y
			- cub->conf.delta_dist.y;
	if (cub->conf.corr_distance < 1e-4)
		cub->conf.corr_distance = 1e-4;
	cub->conf.wall_h = (int)(WIN_Y / cub->conf.corr_distance);
	if (cub->conf.wall_h <= 0)
		cub->conf.wall_h = WIN_Y;
	if (cub->conf.wall_h > WIN_Y * 10)
		cub->conf.wall_h = WIN_Y * 10;
}

void	conduct_dda(t_core *cub)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (cub->conf.side_dist.x < cub->conf.side_dist.y)
		{
			cub->conf.side_dist.x += cub->conf.delta_dist.x;
			cub->conf.map.x += cub->conf.step.x;
			cub->conf.side = VERTICAL;
		}
		else
		{
			cub->conf.side_dist.y += cub->conf.delta_dist.y;
			cub->conf.map.y += cub->conf.step.y;
			cub->conf.side = HORIZONTAL;
		}
		if (cub->map.grid[cub->conf.map.y][cub->conf.map.x] == WALL)
			hit = true;
	}
}

double	get_wall_x(t_core *cub, int side)
{
	double	impact_pos;

	if (side == VERTICAL)
		impact_pos = cub->player1.pos_d.y + cub->conf.corr_distance
			* cub->conf.ray_dir.y;
	else
		impact_pos = cub->player1.pos_d.x + cub->conf.corr_distance
			* cub->conf.ray_dir.x;
	impact_pos -= floor(impact_pos);
	return (impact_pos);
}

void	get_wall_line_idx(t_core *cub)
{
	double	wall_x;
	int		tex_x;
	int		temp;
	int		tex_width;

	cub->conf.draw_start = WIN_Y / 2 - (cub->conf.wall_h / 2)
		+ cub->player1.pitch;
	cub->conf.draw_end = WIN_Y / 2 + (cub->conf.wall_h / 2)
		+ cub->player1.pitch;
	wall_x = get_wall_x(cub, cub->conf.side);
	if (cub->conf.side == HORIZONTAL && cub->conf.ray_dir.y > 0)
		tex_width = cub->graphic.wall[NO].width;
	else if (cub->conf.side == HORIZONTAL && cub->conf.ray_dir.y < 0)
		tex_width = cub->graphic.wall[SO].width;
	else if (cub->conf.side == VERTICAL && cub->conf.ray_dir.x > 0)
		tex_width = cub->graphic.wall[WE].width;
	else
		tex_width = cub->graphic.wall[EA].width;
	tex_x = (int)(wall_x * (double)tex_width);
	if (cub->conf.side == VERTICAL && cub->conf.ray_dir.x < 0)
	{
		temp = tex_x;
		tex_x = tex_width - temp - 1;
	}
	else if (cub->conf.side == HORIZONTAL && cub->conf.ray_dir.y > 0)
	{
		temp = tex_x;
		tex_x = tex_width - temp - 1;
	}
	cub->conf.tex_x = tex_x;
}

void	draw_wall_line(t_core *cub, int idx)
{
	int		target_line_pixel;
	t_wall	target_line_img;
	int		y;
	int		tex_y;
	double	tex_pos;
	int		pixel;
	double	step;
	int		draw_start;
	int		draw_end;

	draw_start = cub->conf.draw_start;
	draw_end = cub->conf.draw_end;
	if (cub->conf.side == HORIZONTAL && cub->conf.ray_dir.y > 0)
		target_line_img = cub->graphic.wall[NO];
	else if (cub->conf.side == HORIZONTAL && cub->conf.ray_dir.y < 0)
		target_line_img = cub->graphic.wall[SO];
	else if (cub->conf.side == VERTICAL && cub->conf.ray_dir.x > 0)
		target_line_img = cub->graphic.wall[WE];
	else
		target_line_img = cub->graphic.wall[EA];
	if (cub->conf.wall_h <= 0)
		cub->conf.wall_h = 1;
	step = (double)target_line_img.height / (double)cub->conf.wall_h;
	tex_pos = (draw_start - (WIN_Y / 2) + cub->conf.wall_h / 2) * step;
	if (draw_start < 0)
	{
		tex_pos += (-draw_start) * step;
		draw_start = 0;
	}
	if (draw_end >= WIN_Y)
		draw_end = WIN_Y - 1;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= target_line_img.height)
			tex_y = target_line_img.height - 1;
		tex_pos += step;
		target_line_pixel = *(int *)(target_line_img.data_addr + tex_y
				* target_line_img.size_line + cub->conf.tex_x
				* (target_line_img.bpp / 8));
		pixel = y * cub->graphic.size_line + idx * (cub->graphic.bpp / 8);
		*(int *)(cub->graphic.data_addr + pixel) = target_line_pixel;
		y++;
	}
}

void	raycast(t_core *cub)
{
	int	idx;

	idx = 0;
	while (idx < WIN_X)
	{
		loop_init_raycast(cub, idx);
		conduct_dda(cub);
		calc_wall_line(cub, idx);
		get_wall_line_idx(cub);
		draw_wall_line(cub, idx);
		idx++;
	}
}
