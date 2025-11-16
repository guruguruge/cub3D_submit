/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_surface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 00:00:00 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 00:00:00 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_digit_char(char c)
{
	return (c >= '0' && c <= '9');
}

static int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static bool	parse_rgb_token(char *token, int *ret_val)
{
	char	*tmp;
	char	*trimmed;
	int		val;

	trimmed = ft_strtrim(token, " \t\r\n");
	if (!trimmed)
		return (false);
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return (false);
	}
	tmp = trimmed;
	while (*tmp)
	{
		if (!is_digit_char(*tmp))
		{
			free(trimmed);
			return (false);
		}
		tmp++;
	}
	val = ft_atoi(trimmed);
	free(trimmed);
	if (val < 0 || val > 255)
		return (false);
	*ret_val = val;
	return (true);
}

void	parse_surface(t_core *cub, char *raw_content, t_parse_state type)
{
	char	**split;
	int		i;

	int r, g, b;
	split = ft_split_target(raw_content, ",");
	if (!split)
		error_print("Malloc error", MALLOC_ERROR, cub);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free_args(split);
		error_print("Invalid RGB format", CONTENT_ERROR, cub);
	}
	if (!parse_rgb_token(split[0], &r) || !parse_rgb_token(split[1], &g)
		|| !parse_rgb_token(split[2], &b))
	{
		free_args(split);
		error_print("Invalid RGB value", CONTENT_ERROR, cub);
	}
	free_args(split);
	if (type == F)
		cub->graphic.surface[F].rgb = create_rgb(r, g, b);
	else if (type == C)
		cub->graphic.surface[C].rgb = create_rgb(r, g, b);
}
