#include "../inc/libft.h"

static int	is_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (is_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while ((end > start) && (is_set(s1[end], set)))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
