#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t count)
{
	size_t	dst_idx;
	size_t	src_idx;

	dst_idx = 0;
	src_idx = 0;
	while (count--)
	{
		dst[dst_idx] = src[src_idx];
		if (src[src_idx])
			src_idx++;
		dst_idx++;
	}
	return (dst);
}
