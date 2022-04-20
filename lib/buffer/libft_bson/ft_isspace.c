#include "libft.h"

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\v' \
	|| c == '\f' || c == '\t');
}
