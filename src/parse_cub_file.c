/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:21:15 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:21:15 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_parse_state	which_component(char *prefix)
{
	if (ft_strcmp(prefix, "NO") == 0)
		return (NO);
	if (ft_strcmp(prefix, "SO") == 0)
		return (SO);
	if (ft_strcmp(prefix, "WE") == 0)
		return (WE);
	if (ft_strcmp(prefix, "EA") == 0)
		return (EA);
	if (ft_strcmp(prefix, "F") == 0)
		return (FLR);
	if (ft_strcmp(prefix, "C") == 0)
		return (CEL);
	else
		return (MAP);
}

void	init_component_struct(t_core *cub)
{
	cub->graphic.surface = ft_calloc(2, sizeof(t_surface));
	if (!cub->graphic.surface)
		error_print("Malloc fail", MALLOC_ERROR, cub);
	cub->graphic.wall = ft_calloc(4, sizeof(t_wall));
	if (!cub->graphic.wall)
		error_print("Malloc fail", MALLOC_ERROR, cub);
	cub->map.grid = ft_calloc((size_t)cub->raw_col_size, sizeof(char *));
	if (!cub->map.grid)
		error_print("Malloc fail", MALLOC_ERROR, cub);
	cub->map.size.x = 0;
	cub->map.size.y = 0;
	cub->map.grid[0] = NULL;
	cub->parse_checker[NO] = false;
	cub->parse_checker[SO] = false;
	cub->parse_checker[WE] = false;
	cub->parse_checker[EA] = false;
	cub->parse_checker[FLR] = false;
	cub->parse_checker[CEL] = false;
}

void	get_raw_content(t_core *cub)
{
	int		i;
	char	*tmp_gnl;

	cub->raw_input = malloc((cub->raw_col_size + 1) * sizeof(char *));
	if (!cub->raw_input)
		error_print("Malloc fail", MALLOC_ERROR, cub);
	i = 0;
	while (i < cub->raw_col_size)
	{
		cub->raw_input[i] = get_next_line(cub->map.fd);
		if (!cub->raw_input[i])
		{
			free_args_fail(cub->raw_input, i);
			error_print("Malloc fail", MALLOC_ERROR, cub);
		}
		i++;
	}
	cub->raw_input[i] = NULL;
	tmp_gnl = get_next_line(cub->map.fd);
	if (tmp_gnl != NULL)
		free(tmp_gnl);
	close(cub->map.fd);
}

void	check_file_content(t_core *cub)
{
	int		i;
	char	*line_prefix;

	i = 0;
	cub->parse_state = INIT;
	while (cub->raw_input[i])
	{
		if (cub->parse_state != MAP && is_emptyline(cub->raw_input[i]))
			i++;
		else
		{
			line_prefix = skip_space(cub->raw_input[i]);
			if (cub->parse_state != MAP)
				cub->parse_state = which_component(line_prefix);
			if (cub->parse_state != MAP)
				parse_component(cub, skip_space(cub->raw_input[i]));
			else if (!check_content_fulfill(cub->parse_checker))
				error_print("Invalid Content", CONTENT_ERROR, cub);
			else
				parse_map(cub, cub->raw_input[i]);
			i++;
		}
	}
	cub->map.grid[cub->map.size.y] = NULL;
}

void	parse_cub_file(t_core *cub, char *input)
{
	cub->map.fd = open(input, O_RDONLY);
	get_raw_content(cub);
	init_component_struct(cub);
	check_file_content(cub);
	check_texturefile_sanity(cub);
	check_mapcontent_sanity(cub);
	check_mapstructure_sanity(cub);
}
