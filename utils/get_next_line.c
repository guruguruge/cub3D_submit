/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 12:54:22 by sguruge           #+#    #+#             */
/*   Updated: 2025-05-11 12:54:22 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*get_next_line(int fd)
{
	static size_t	location = 0;
	static char		*buffer = NULL;
	t_gnl			gnl;
	char			*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > REASONABLE_SIZE)
		return (NULL);
	gnl.line = NULL;
	gnl.temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!gnl.temp)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(1, sizeof(char));
		if (!buffer)
			return (free(gnl.temp), NULL);
	}
	result = gnl_read_process(fd, &gnl, &buffer, &location);
	free(gnl.temp);
	return (result);
}

char	*gnl_read_process(int fd, t_gnl *gnl, char **buf, size_t *loc)
{
	ssize_t	read_b;

	*gnl = gnl_process_buffer(*gnl, *loc, *buf, ft_strlen(*buf));
	if (gnl->line)
	{
		*loc = gnl->i + 1;
		return (gnl->line);
	}
	read_b = read(fd, gnl->temp, BUFFER_SIZE);
	while (read_b > 0)
	{
		gnl->temp[read_b] = '\0';
		*buf = ft_strjoin_gnl(*buf, gnl->temp);
		if (!*buf)
			return (NULL);
		*gnl = gnl_process_buffer(*gnl, *loc, *buf, ft_strlen(*buf));
		if (gnl->line)
		{
			*loc = gnl->i + 1;
			return (gnl->line);
		}
		read_b = read(fd, gnl->temp, BUFFER_SIZE);
	}
	return (gnl_handle_eof(gnl, buf, loc, read_b));
}

t_gnl	gnl_process_buffer(t_gnl gnl, size_t loc, char *buf, size_t buf_len)
{
	gnl.i = loc;
	if (!buf || buf_len == 0)
	{
		gnl.line = NULL;
		return (gnl);
	}
	while (gnl.i < buf_len)
	{
		if (buf[gnl.i] == '\n')
		{
			gnl.line = ft_substr(buf, loc, gnl.i - loc + 1);
			return (gnl);
		}
		gnl.i++;
	}
	gnl.line = NULL;
	return (gnl);
}

char	*gnl_handle_eof(t_gnl *gnl, char **buffer, size_t *loc, ssize_t read_b)
{
	if (read_b == 0 && *buffer && (*buffer)[*loc])
	{
		gnl->line = ft_strdup(*buffer + *loc);
		free(*buffer);
		*buffer = NULL;
		*loc = 0;
		return (gnl->line);
	}
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	*loc = 0;
	return (NULL);
}
