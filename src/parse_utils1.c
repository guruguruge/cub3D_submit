#include "../inc/cub3d.h"

bool	is_emptyline(char *str);
char	*skip_space(char *str);
bool	is_space(char c);
char	*parse_duplicate(char *raw_content);

bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	return (&str[i]);
}

bool	is_emptyline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		if (!is_space(str[i]))
			return (false);
		i++;
	}
	return (true);
}

char	*parse_duplicate(char *raw_content)
{
	int		size;
	int		i;
	char	*res;

	size = 0;
	i = 0;
	while (raw_content[size] && !is_space(raw_content[size]))
		size++;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = raw_content[i];
		i++;
	}
	res[i] = '\0';
	// printf("%s : ", raw_content);
	// printf("%s \n", res);
	return (res);
}

char	*skip_to_next(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_space(str[i]))
		i++;
	while (str[i] && is_space(str[i]))
		i++;
	return (&str[i]);
}
