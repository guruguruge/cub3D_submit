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
		if (cub->conf.map.x < 0 || cub->conf.map.x >= cub->map.size.x || cub->conf.map.y < 0 || cub->conf.map.y >= cub->map.size.y)
			hit = true; 
		else if (cub->map.grid[cub->conf.map.y][cub->conf.map.x] == WALL)
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

void	print_raycast_debug(t_core *cub, int screen_x)
{
	t_raycast	*ray;

	// cub->confだと長いので、短い変数名にエイリアスします
	ray = &cub->conf;
	printf("\n\033[1;36m--- DEBUG RAY at screen_x: %d ---\033[0m\n", screen_x);
	printf("----------------------------------------\n");
	printf("\033[1;33m## 1. Player Config\033[0m\n");
	printf("player deg %f\n", (cub->player1.deg_radian / TO_RADIAN));
	printf("player pos int (x,y) (%d %d)\n", cub->player1.pos.x,
		cub->player1.pos.y);
	printf("player pos double (x,y) (%f %f)\n", cub->player1.pos_d.x,
		cub->player1.pos_d.y);
	// 1. レイの初期設定値
	printf("\n\033[1;33m## 2. Initial Ray Setup\033[0m\n");
	printf("camera_x      : %.4f\n", ray->camera_x);
	printf("ray_dir (x,y) : (%.4f, %.4f)\n", ray->ray_dir.x, ray->ray_dir.y);
	printf("map (start)   : (%d, %d)\n", ray->map.x, ray->map.y);
	// 2. DDAアルゴリズムの計算値
	printf("\n\033[1;33m## 3. DDA Algorithm Variables\033[0m\n");
	printf("step (x,y)      : (%d, %d)\n", ray->step.x, ray->step.y);
	printf("delta_dist(x,y) : (%.4f, %.4f)\n", ray->delta_dist.x,
		ray->delta_dist.y);
	printf("side_dist (x,y) : (%.4f, %.4f)\n", ray->side_dist.x,
		ray->side_dist.y);
	// 3. DDA実行後の結果 (まだ計算していない場合は0や不定値が表示されます)
	printf("\n\033[1;33m## 4. DDA Result\033[0m\n");
	if (ray->side == 0)
		printf("side (hit)      : %d (X-side: East/West)\n", ray->side);
	else
		printf("side (hit)      : %d (Y-side: North/South)\n", ray->side);
	printf("corr_distance   : %.4f\n", ray->corr_distance);
	printf("wall_h          : %.4f\n", ray->wall_h);
	printf("----------------------------------------\n");
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
		// if(idx == WIN_X / 2)
		// 	print_raycast_debug(cub, idx);
		idx++;
	}
}
