/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-29 07:54:36 by sguruge           #+#    #+#             */
/*   Updated: 2025-04-29 07:54:36 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	print_unsigned(va_list *word, int *io_error)
{
	unsigned int	word_unsi;
	int				i;
	char			*word_unsi_c;

	i = 0;
	word_unsi = va_arg(*word, unsigned int);
	word_unsi_c = ft_unitoa_base(word_unsi, 10, 'x');
	while (word_unsi_c[i])
	{
		*io_error = write(1, &word_unsi_c[i], 1);
		i++;
	}
	free(word_unsi_c);
	return (i);
}

int	print_address(va_list *word, int *io_error)
{
	void			*word_address;
	unsigned long	word_address_n;
	int				i;
	char			*word_address_c;

	i = 0;
	word_address = va_arg(*word, void *);
	if (word_address == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	word_address_n = (uintptr_t)word_address;
	word_address_c = ft_unltoa_base(word_address_n, 16, 'x');
	write(1, "0x", 2);
	while (word_address_c[i])
	{
		*io_error = write(1, &word_address_c[i], 1);
		i++;
	}
	free(word_address_c);
	return (i + 2);
}
