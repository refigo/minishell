#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t count)
{
	size_t	dst_idx;
	size_t	src_idx;

	src_idx = 0;
	dst_idx = 0;
	while (dst[dst_idx])
		dst_idx++;
	while (count--)
	{
		dst[dst_idx] = src[src_idx];
		if (!dst[dst_idx])
			break ;
		dst_idx++;
		src_idx++;
	}
	dst[dst_idx] = '\0';
	return (dst);
}
