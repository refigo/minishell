#include "libft.h"
#include <stdio.h>

void	ft_assert(int flag, char *str)
{
	if (flag != 0)
		return ;
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}
