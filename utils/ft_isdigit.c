#include "../inc/libft.h"

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return ((c >= '0') && (c <= '9'));
	else
		return (0);
}
