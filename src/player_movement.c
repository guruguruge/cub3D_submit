/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-14 06:08:45 by sguruge           #+#    #+#             */
/*   Updated: 2025-08-14 06:08:45 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    move_forward(t_core *cub);
void    move_left(t_core *cub);
void    move_right(t_core *cub);
void    move_back(t_core *cub);

void    move_forward(t_core *cub)
{
    t_pointd temp_d;
    t_point temp;
    double      move_step;

    move_step = STEP * cub->d_time;


    temp_d.x = cub->player1.pos_d.x + move_step * fast_cos(cub->player1.deg_radian, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step * fast_sin(cub->player1.deg_radian, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if(cub->map.grid[temp.y][temp.x] == WALL)
        return ;
    else
    {
        cub->player1.pos_d = temp_d;
        cub->player1.pos = temp;
    }
}

void    move_left(t_core *cub)
{    
    t_pointd temp_d;
    t_point temp;
    double      move_step;
    
    move_step = STEP * cub->d_time;

    temp_d.x = cub->player1.pos_d.x + move_step * fast_cos(cub->player1.deg_radian + PI * 1.5, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step * fast_sin(cub->player1.deg_radian + PI * 1.5, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if(cub->map.grid[temp.y][temp.x] == WALL)
        return ;
    else
    {
        cub->player1.pos_d = temp_d;
        cub->player1.pos = temp;
    }
}

void    move_right(t_core *cub)
{
    t_pointd temp_d;
    t_point temp;
    double      move_step;
    
    move_step = STEP * cub->d_time;

    temp_d.x = cub->player1.pos_d.x + move_step * fast_cos(cub->player1.deg_radian + PI * 0.5, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step * fast_sin(cub->player1.deg_radian + PI * 0.5, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if(cub->map.grid[temp.y][temp.x] == WALL)
        return ;
    else
    {
        cub->player1.pos_d = temp_d;
        cub->player1.pos = temp;
    }
}

void    move_back(t_core *cub)
{
    t_pointd temp_d;
    t_point temp;
    double      move_step;
    
    move_step = STEP * cub->d_time;
    temp_d.x = cub->player1.pos_d.x + move_step * fast_cos(cub->player1.deg_radian + PI, *cub);
    temp_d.y = cub->player1.pos_d.y + move_step * fast_sin(cub->player1.deg_radian + PI, *cub);
    temp.x = (int)temp_d.x;
    temp.y = (int)temp_d.y;
    if(cub->map.grid[temp.y][temp.x] == WALL)
        return ;
    else
    {
        cub->player1.pos_d = temp_d;
        cub->player1.pos = temp;
    }
}
