/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-03 22:38:18 by sguruge           #+#    #+#             */
/*   Updated: 2025-07-03 22:38:18 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
}

void	error_print(char *message, int type, t_core *cub)
{
	(void)cub;
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	if (cub)
		free_all(cub);
	exit(type);
}

int	main(int argc, char **argv)
{
	t_core	*cub;

	cub = malloc(sizeof(t_core));
	if (!cub)
		error_print("malloc fail", MALLOC_ERROR, cub);
	check_args(argc, argv, cub);
	parse_cub_file(cub, argv[1]);
	init_mlx(cub);
	main_loop(cub);
	free_all(cub);
	return (EXIT_SUCCESS);
}
