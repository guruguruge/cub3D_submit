/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguruge <sguruge@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 12:54:12 by sguruge           #+#    #+#             */
/*   Updated: 2025-05-11 12:54:12 by sguruge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*mem;

// 	if (nmemb && size > __SIZE_MAX__ / nmemb)
// 		return (NULL);
// 	mem = (void *)malloc((nmemb * size));
// 	if (!mem)
// 		return (NULL);
// 	ft_memset(mem, 0, nmemb * size);
// 	return (mem);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	total_len;
	char	*j_str;
	size_t	i;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	total_len = s1_len + ft_strlen(s2);
	j_str = (char *)malloc((total_len + 1) * sizeof(char));
	if (!j_str)
		return (free(s1), NULL);
	i = -1;
	while (++i < s1_len)
		j_str[i] = s1[i];
	i = -1;
	while (++i < total_len - s1_len)
		j_str[s1_len + i] = s2[i];
	j_str[total_len] = '\0';
	return (free(s1), j_str);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*sub;
// 	size_t	i;
// 	size_t	sub_len;

// 	if (!s || start > ft_strlen(s))
// 	{
// 		sub = ft_calloc(1, sizeof(char));
// 		return (sub);
// 	}
// 	i = 0;
// 	sub_len = (ft_strlen(s)) - start;
// 	if (sub_len > len)
// 		sub_len = len;
// 	sub = (char *)malloc((sub_len + 1) * sizeof(char));
// 	if (!sub)
// 		return (NULL);
// 	while ((i < len) && (s[start + i]))
// 	{
// 		sub[i] = s[start + i];
// 		i++;
// 	}
// 	sub[i] = '\0';
// 	return (sub);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*dup;
// 	size_t	i;

// 	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
