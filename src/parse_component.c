/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_component.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:21:20 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:21:20 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	assert_component_available(t_core *cub, t_parse_state state)
{
	if (state < NO || state > CEL)
		return ;
	if (cub->parse_checker[state])
		error_print("Duplicate identifier", CONTENT_ERROR, cub);
}

static void	set_component_flag(t_core *cub, t_parse_state state)
{
	if (state < NO || state > CEL)
		return ;
	cub->parse_checker[state] = true;
}

bool	check_content_fulfill(bool *checker)
{
	if (!checker[NO] || !checker[SO] || !checker[EA] || !checker[WE]
		|| !checker[FLR] || !checker[CEL])
		return (false);
	else
		return (true);
}

void	parse_component(t_core *cub, char *line_prefix)
{
	char	*raw_content;
	char	*next_token;

	raw_content = skip_to_next(line_prefix);
	if (*raw_content == '\0' || *raw_content == '\n')
		error_print("Invalid content", CONTENT_ERROR, cub);
	assert_component_available(cub, cub->parse_state);
	if (cub->parse_state == FLR)
	{
		parse_surface(cub, raw_content, F);
		set_component_flag(cub, FLR);
	}
	else if (cub->parse_state == CEL)
	{
		parse_surface(cub, raw_content, C);
		set_component_flag(cub, CEL);
	}
	else if (cub->parse_state == NO)
	{
		cub->graphic.wall[NO].path = parse_duplicate(raw_content);
		next_token = skip_to_next(raw_content);
		if (*next_token != '\0' && *next_token != '\n')
			error_print("Invalid content", CONTENT_ERROR, cub);
		set_component_flag(cub, NO);
	}
	else if (cub->parse_state == SO)
	{
		cub->graphic.wall[SO].path = parse_duplicate(raw_content);
		next_token = skip_to_next(raw_content);
		if (*next_token != '\0' && *next_token != '\n')
			error_print("Invalid content", CONTENT_ERROR, cub);
		set_component_flag(cub, SO);
	}
	else if (cub->parse_state == WE)
	{
		cub->graphic.wall[WE].path = parse_duplicate(raw_content);
		next_token = skip_to_next(raw_content);
		if (*next_token != '\0' && *next_token != '\n')
			error_print("Invalid content", CONTENT_ERROR, cub);
		set_component_flag(cub, WE);
	}
	else if (cub->parse_state == EA)
	{
		cub->graphic.wall[EA].path = parse_duplicate(raw_content);
		next_token = skip_to_next(raw_content);
		if (*next_token != '\0' && *next_token != '\n')
			error_print("Invalid content", CONTENT_ERROR, cub);
		set_component_flag(cub, EA);
	}
}

void	check_texturefile_sanity(t_core *cub)
{
	int		i;
	int		fd;
	char	*path;
	size_t	len;

	i = NO;
	while (i <= EA)
	{
		path = cub->graphic.wall[i].path;
		if (!path || path[0] == '\0')
			error_print("Texture path missing", TEXTURE_CONTENT_ERROR, cub);
		len = ft_strlen(path);
		if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
			error_print("Texture must be .xpm", TEXTURE_CONTENT_ERROR, cub);
		fd = open(path, O_RDONLY);
		if (fd < 0)
			error_print("Cannot open texture file", TEXTURE_CONTENT_ERROR, cub);
		close(fd);
		i++;
	}
}
