/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-29 07:54:03 by sguruge           #+#    #+#             */
/*   Updated: 2025-04-29 07:54:03 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	print_char(va_list *word, int *io_error)
{
	char	word_char;

	word_char = (char)va_arg(*word, int);
	*io_error = write(1, &word_char, 1);
	return (1);
}

int	print_str(va_list *word, int *io_error)
{
	char	*word_str;
	int		i;

	i = 0;
	word_str = va_arg(*word, char *);
	if (word_str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (word_str[i])
	{
		*io_error = write(1, &word_str[i], 1);
		i++;
	}
	return (i);
}

int	print_deci(va_list *word, int *io_error)
{
	int		word_deci;
	int		i;
	char	*word_deci_c;

	i = 0;
	word_deci = va_arg(*word, int);
	word_deci_c = ft_itoa(word_deci);
	while (word_deci_c[i])
	{
		*io_error = write(1, &word_deci_c[i], 1);
		i++;
	}
	free(word_deci_c);
	return (i);
}

int	print_hex(va_list *word, int *io_error, char format)
{
	unsigned int	word_hex;
	int				i;
	char			*word_hex_c;

	i = 0;
	word_hex = va_arg(*word, unsigned int);
	word_hex_c = ft_unitoa_base(word_hex, 16, format);
	while (word_hex_c[i])
	{
		*io_error = write(1, &word_hex_c[i], 1);
		i++;
	}
	free(word_hex_c);
	return (i);
}
