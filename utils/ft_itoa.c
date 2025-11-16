/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-29 05:19:42 by sguruge           #+#    #+#             */
/*   Updated: 2025-04-29 05:19:42 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	intlen(int n)
{
	size_t	size;
	long	num;

	num = (long)n;
	size = 0;
	if (num <= 0)
		size = 1;
	if (num < 0)
		num = -num;
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;
	long	num;

	num = (long)n;
	len = intlen(num);
	result = (char *)malloc((len + 1) * (sizeof(char)));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num == 0)
		result[0] = '0';
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		result[--len] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}
