/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-16 12:20:23 by sguruge           #+#    #+#             */
/*   Updated: 2025-11-16 12:20:23 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_col_size(int fd, int *ptr);
void	check_args(int ac, char **av, t_core *cub);

void	get_col_size(int fd, int *ptr)
{
	int		i;
	char	*line;

	i = 0;
	line = "init";
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		i++;
	}
	*ptr = i;
}

void	check_args(int ac, char **av, t_core *cub)
{
	int	i;
	int	temp;

	if (ac != 2)
		error_print("Invalid number of args", ARG_ERROR, cub);
	i = 0;
	while (av[1][i])
		i++;
	if (ft_strncmp(&av[1][i - 4], ".cub", 4) != 0)
		error_print("Invalid file type", ARG_ERROR, cub);
	temp = open(av[1], O_RDONLY);
	if (temp < 0)
	{
		close(temp);
		error_print("Unopenable file", ARG_ERROR, cub);
	}
	get_col_size(temp, &cub->raw_col_size);
	close(temp);
}
