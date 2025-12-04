/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-13 21:20:47 by sguruge           #+#    #+#             */
/*   Updated: 2025-08-13 21:20:47 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

double	get_radian(double deg)
{
	return (PI * (deg / 180));
}

void	draw_surfaces(t_core *cub, int bits_per_pixel, int size_line)
{
	t_point	p;
	int		row_int;
	int		*buf;
	int		base;
	int		color;

	(void)bits_per_pixel;
	row_int = size_line / 4;
	buf = (int *)cub->graphic.data_addr;
	p.y = 0;
	while (p.y < WIN_Y)
	{
		base = p.y * row_int;
		if (p.y < WIN_Y / 2)
			color = cub->graphic.surface[C].rgb;
		else
			color = cub->graphic.surface[F].rgb;
		p.x = 0;
		while (p.x < WIN_X)
		{
			buf[base + p.x] = color;
			p.x++;
		}
		p.y++;
	}
}

void	init_frame(t_core *cub)
{
	if (cub->graphic.frame == NULL)
	{
		cub->graphic.frame = mlx_new_image(cub->mlx.p, WIN_X, WIN_Y);
		cub->graphic.data_addr = mlx_get_data_addr(cub->graphic.frame,
				&cub->graphic.bpp, &cub->graphic.size_line,
				&cub->graphic.endian);
	}
	draw_surfaces(cub, cub->graphic.bpp, cub->graphic.size_line);
}

void	print_frame(t_core *cub)
{
	mlx_put_image_to_window(cub->mlx.p, cub->mlx.win, cub->graphic.frame, 0, 0);
}

int	render(void *cub_v)
{
	t_core			*cub;
	struct timeval	now;
	double			elapsed;
	const double	target_frame = 1.0 / 30.0;

	cub = (t_core *)cub_v;
	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - cub->last_update_time.tv_sec) + (now.tv_usec
			- cub->last_update_time.tv_usec) / 1e6;
	if (elapsed < target_frame)
		return (0);
	cub->d_time = elapsed;
	cub->last_update_time = now;
	init_frame(cub);
	raycast(cub);
	print_frame(cub);
	return (0);
}

void	end_game(t_core *cub)
{
	free_all(cub);
	exit(0);
}

void	adjust_player_radian(t_core *cub)
{
	if (cub->player1.deg_radian > 2 * PI)
		cub->player1.deg_radian -= 2 * PI;
	else if (cub->player1.deg_radian < 0)
		cub->player1.deg_radian += 2 * PI;
}

int	key_press(int key_code, void *cub_v)
{
	t_core	*cub;

	cub = (t_core *)cub_v;
	if (key_code == KEY_ESC)
		end_game(cub);
	if (key_code == KEY_L)
		cub->player1.deg_radian -= ROTSPEED * cub->d_time * TO_RADIAN;
	else if (key_code == KEY_R)
		cub->player1.deg_radian += ROTSPEED * cub->d_time * TO_RADIAN;
	else if (key_code == KEY_W)
		move_forward(cub);
	else if (key_code == KEY_A)
		move_left(cub);
	else if (key_code == KEY_S)
		move_back(cub);
	else if (key_code == KEY_D)
		move_right(cub);
	adjust_player_radian(cub);
	calculate_vectors(cub);
	return (0);
}

int	close_window(void *cub_v)
{
	t_core	*cub;

	cub = (t_core *)cub_v;
	free_all(cub);
	exit(0);
	return (0);
}

void	main_loop(t_core *cub)
{
	void	*cub_v;

	cub_v = (void *)cub;
	init_frame(cub);
	gettimeofday(&cub->last_update_time, NULL);
	mlx_hook(cub->mlx.win, KEY_PRESS, KEY_PRESS_M, key_press, cub_v);
	mlx_hook(cub->mlx.win, CLOSE_WINDOW, CLOSE_WINDOW_M, close_window, cub_v);
	mlx_loop_hook(cub->mlx.p, *render, cub_v);
	mlx_loop(cub->mlx.p);
}
