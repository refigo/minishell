#include "libft.h"

void	ft_free(void **ptr)
{
	if (!(ptr && *ptr))
		return ;
	free(*ptr);
	*ptr = (void *)0;
}
