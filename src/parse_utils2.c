#include "../inc/cub3d.h"

static bool	is_target(char c, char *target)
{
	int	i;

	i = 0;
	while (target[i])
	{
		if (target[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static size_t	ft_count_istarget(char const *s, char *target)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s && is_target(*s, target))
			s++;
		if (*s)
		{
			cnt++;
			while (*s && !is_target(*s, target))
				s++;
		}
	}
	return (cnt);
}

static char	*word_splitter_istarget(char const *s, char *target)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && !is_target(s[i], target))
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	word[i] = '\0';
	i = 0;
	while (s[i] && !is_target(s[i], target))
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

static char	**free_and_fail(char **words, size_t allocated_count)
{
	size_t	i;

	i = 0;
	while (i < allocated_count)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

char	**ft_split_target(char const *s, char *target)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**words;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len = ft_count_istarget(s, target);
	words = (char **)malloc(sizeof(char *) * (len + 1));
	if (!words)
		return (NULL);
	while (i < len)
	{
		while (s[j] && is_target(s[j], target))
			j++;
		words[i] = word_splitter_istarget(s + j, target);
		if (!words[i])
			return (free_and_fail(words, i));
		while (s[j] && !is_target(s[j], target))
			j++;
		i++;
	}
	return (words[len] = NULL, words);
}
