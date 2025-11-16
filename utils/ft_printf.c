/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-29 07:54:24 by sguruge           #+#    #+#             */
/*   Updated: 2025-04-29 07:54:24 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	error_handle(va_list *word)
{
	va_end(*word);
	return (-1);
}

int	print_word(char format, int *word_num)
{
	int	io_error;

	io_error = write(1, &format, 1);
	if (io_error == -1)
		return (0);
	(*word_num)++;
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	word;
	size_t	i;
	int		word_num;

	va_start(word, format);
	i = 0;
	word_num = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (handle_conversion(format[i + 1], &word, &word_num))
				i += 2;
			else
				return (error_handle(&word));
		}
		else if (print_word(format[i], &word_num))
			i++;
		else
			return (error_handle(&word));
	}
	va_end(word);
	return (word_num);
}

int	handle_conversion(char format, va_list *word, int *word_num)
{
	int	io_error;

	io_error = 0;
	if (format == 'c')
		*word_num += print_char(word, &io_error);
	else if (format == 's')
		*word_num += print_str(word, &io_error);
	else if ((format == 'd') || (format == 'i'))
		*word_num += print_deci(word, &io_error);
	else if ((format == 'x') || (format == 'X'))
		*word_num += print_hex(word, &io_error, format);
	else if (format == 'u')
		*word_num += print_unsigned(word, &io_error);
	else if (format == 'p')
		*word_num += print_address(word, &io_error);
	else if (format == '%')
	{
		io_error = write(1, "%", 1);
		(*word_num)++;
	}
	else if (io_error == -1)
		return (0);
	else
		return (0);
	return (1);
}
