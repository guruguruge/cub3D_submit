/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:21:43 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:21:43 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_core *cub);
void	move_left(t_core *cub);
void	move_right(t_core *cub);
void	move_back(t_core *cub);

static bool	is_wall_or_space(t_core *cub, int x, int y)
{
    int	row_len;

    if (y < 0 || y >= cub->map.size.y)
        return (true);
    row_len = (int)ft_strlen(cub->map.grid[y]);
    if (x < 0 || x >= row_len)
        return (true);
    if (cub->map.grid[y][x] == WALL || cub->map.grid[y][x] == ' ')
        return (true);
    return (false);
}

static bool	can_move_to(t_core *cub, t_point dest)
{
    if (is_wall_or_space(cub, cub->player1.pos.x, dest.y))
        return (false);
    if (is_wall_or_space(cub, dest.x, cub->player1.pos.y))
        return (false);
    if (is_wall_or_space(cub, dest.x, dest.y))
        return (false);
    return (true);
}

void	move_forward(t_core *cub)
{
    t_pointd	temp_d;
    t_point		temp;
    double		move_step;

    move_step = STEP * cub->d_time;
    temp_d.x = cub->player1.pos_d.x + move_step
        * fast_cos(cub->player1.deg_radian, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step
        * fast_sin(cub->player1.deg_radian, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if (!can_move_to(cub, temp))
        return ;
    cub->player1.pos_d = temp_d;
    cub->player1.pos = temp;
}

void	move_left(t_core *cub)
{
    t_pointd	temp_d;
    t_point		temp;
    double		move_step;

    move_step = STEP * cub->d_time;
    temp_d.x = cub->player1.pos_d.x + move_step
        * fast_cos(cub->player1.deg_radian + PI * 1.5, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step
        * fast_sin(cub->player1.deg_radian + PI * 1.5, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if (!can_move_to(cub, temp))
        return ;
    cub->player1.pos_d = temp_d;
    cub->player1.pos = temp;
}

void	move_right(t_core *cub)
{
    t_pointd	temp_d;
    t_point		temp;
    double		move_step;

    move_step = STEP * cub->d_time;
    temp_d.x = cub->player1.pos_d.x + move_step
        * fast_cos(cub->player1.deg_radian + PI * 0.5, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step
        * fast_sin(cub->player1.deg_radian + PI * 0.5, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if (!can_move_to(cub, temp))
        return ;
    cub->player1.pos_d = temp_d;
    cub->player1.pos = temp;
}

void	move_back(t_core *cub)
{
    t_pointd	temp_d;
    t_point		temp;
    double		move_step;

    move_step = STEP * cub->d_time;
    temp_d.x = cub->player1.pos_d.x + move_step
        * fast_cos(cub->player1.deg_radian + PI, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step
        * fast_sin(cub->player1.deg_radian + PI, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if (!can_move_to(cub, temp))
        return ;
    cub->player1.pos_d = temp_d;
    cub->player1.pos = temp;
}