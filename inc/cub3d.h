/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-03 22:01:32 by sguruge           #+#    #+#             */
/*   Updated: 2025-07-03 22:01:32 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WALL '1'

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_SPACE 32
# define KEY_L 65361
# define KEY_R 65363

# define KEY_ESC 65307

# define KEY_PRESS 2
# define KEY_PRESS_M 1L << 0

# define WIN_X 1920
# define WIN_Y 1080

# define STEP 5
# define ROTSPEED 90
# define TO_RADIAN 0.01745329251

# define VERTICAL 0
# define HORIZONTAL 1

# define FOV 45
# define H_WALL 1.0

# define PI 3.14159265358979323846

// error numbers
# define ARG_ERROR -1
# define MALLOC_ERROR -2
# define CONTENT_ERROR -3
# define TEXTURE_CONTENT_ERROR -4
# define MAP_CONTENT_ERROR -5

typedef enum e_parse_state
{
	INIT = -2,
	MAP = -1,
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	FLR = 4,
	CEL = 5,
	F = 0,
	C = 1,
}					t_parse_state;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_pointd
{
	double			x;
	double			y;
}					t_pointd;

typedef struct s_map
{
	int				fd;
	char			**grid;
	t_point			size;
}					t_map;

typedef struct s_wall
{
	t_parse_state	dir;
	char			*path;
	void			*ptr;
	int				bpp;
	int				size_line;
	int				endian;
	char			*data_addr;
}					t_wall;

typedef struct s_surface
{
	int				rgb;
	void			*ptr;
}					t_surface;

typedef struct s_back
{
	t_wall			*wall;
	t_surface		*surface;
	void			*frame;
	int				bpp;
	int				size_line;
	int				endian;
	char			*data_addr;
}					t_back;

typedef struct s_mlx
{
	void			*p;
	void			*win;
}					t_mlx;

typedef struct s_raycast
{
	double			fov;

	double			camera_x;
	t_pointd		ray_dir;
	t_point			map;

	t_point			step;
	t_pointd		delta_dist;
	t_pointd		side_dist;

	int				side;
	double			corr_distance;
	double			wall_h;

	int				draw_start;
	int				draw_end;
	int				tex_x;
}					t_raycast;

typedef struct s_player
{
	t_point			pos;
	t_pointd		pos_d;
	double			deg_radian;
	t_pointd		dir_vec;
	t_pointd		plane_vec;
	double			pitch;
}					t_player;

# define RADIAN_PRECISION 6284
# define RATIO_PRECISION 10000
# define PU_1000 3141

typedef struct s_trig_table
{
	double			sin_table[RADIAN_PRECISION];
	double			cos_table[RADIAN_PRECISION];
	double			atan_table[RATIO_PRECISION];
}					t_trig_table;

typedef struct s_core
{
	t_mlx			mlx;
	t_back			graphic;
	t_raycast		conf;

	t_trig_table	trig_table;

	char			**raw_input;
	char			**parsed_input;
	int				raw_col_size;
	t_parse_state	parse_state;
	bool			parse_checker[6];
	t_map			map;

	t_player		player1;
	struct timeval	last_update_time;
	double			d_time;

}					t_core;

void				print_args(char **args);
void				error_print(char *message, int type, t_core *cub);

void				get_col_size(int fd, int *ptr);
void				check_args(int ac, char **av, t_core *cub);

bool				is_emptyline(char *str);
char				*skip_space(char *str);
bool				is_space(char c);
char				*parse_duplicate(char *raw_content);

char				**ft_split_target(char const *s, char *target);

void				parse_cub_file(t_core *cub, char *input);
void				get_raw_content(t_core *cub);
void				init_component_struct(t_core *cub);
void				check_file_content(t_core *cub);
void				parse_component(t_core *cub, char *line_prefix);
bool				check_content_fulfill(bool *checker);
void				parse_surface(t_core *cub, char *raw_content,
						t_parse_state type);
void				check_texturefile_sanity(t_core *cub);
void				check_mapcontent_sanity(t_core *cub);
t_parse_state		which_component(char *prefix);
void				parse_map(t_core *cub, char *map_line);
void				take_off_newline(char *map_line);
void				check_mapstructure_sanity(t_core *cub);

char				**create_padded_map_copy(t_core *cub, t_point map_size,
						t_point *tmp_size);
int					in_targets(char c, char *targets);
void				fill(char **tab, t_point size, t_point cur, char *targets);

char				*skip_to_next(char *str);

void				get_wall_img(t_core *cub);
void				init_raycast_config(t_core *cub);
void				init_mlx(t_core *cub);

void				move_forward(t_core *cub);
void				move_left(t_core *cub);
void				move_right(t_core *cub);
void				move_back(t_core *cub);

double				get_radian(double deg);

void				init_trig_table(t_core *cub);
double				fast_sin(double radian, t_core cub);
double				fast_cos(double radian, t_core cub);
double				fast_atan2(double y, double x, t_core cub);
void				calculate_vectors(t_core *cub);

void				end_game(t_core *cub);
void				raycast(t_core *cub);
void				calc_delta_time(t_core *cub);
void				main_loop(t_core *cub);

void				free_all(t_core *cub);
void				free_args(char **args);
void				free_args_fail(char **args, int size);

#endif
