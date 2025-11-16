/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 11:04:48 by sguruge           #+#    #+#             */
/*   Updated: 2025-05-01 11:04:48 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_unltoa_base(uintptr_t n, int base, char alph_cap)
{
	char	*str;
	size_t	len;
	char	*base_digits;

	if (alph_cap == 'x')
		base_digits = "0123456789abcdef";
	else if (alph_cap == 'X')
		base_digits = "0123456789ABCDEF";
	if (n == 0)
		len = 1;
	else
		len = unllen_base(n, base);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[--len] = base_digits[n % base];
		n /= base;
	}
	return (str);
}

char	*ft_unitoa_base(unsigned int n, int base, char alph_cap)
{
	char	*str;
	size_t	len;
	char	*base_digits;

	if (alph_cap == 'x')
		base_digits = "0123456789abcdef";
	else if (alph_cap == 'X')
		base_digits = "0123456789ABCDEF";
	if (n == 0)
		len = 1;
	else
		len = unintlen_base(n, base);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[--len] = base_digits[n % base];
		n /= base;
	}
	return (str);
}

size_t	unllen_base(unsigned long n, int base)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

size_t	unintlen_base(unsigned int n, int base)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}
