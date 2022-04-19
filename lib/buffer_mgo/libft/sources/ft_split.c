/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:45:47 by mgo               #+#    #+#             */
/*   Updated: 2021/05/20 22:03:15 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_str(char **splitted, int str_len, int i)
{
	splitted[i] = (char *)malloc(str_len + 1);
	if (!splitted[i])
	{
		while (--i >= 0)
			free(splitted[i]);
		free(splitted);
		return (0);
	}
	return (1);
}

static int	spt_len(char const *s, char c)
{
	int		len;

	len = 0;
	while ((s[len] != c) && (s[len] != '\0'))
		len++;
	return (len);
}

static int	spt_size(char const *s, char c)
{
	int		arr_size;

	arr_size = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			arr_size++;
			while ((*s != c) && (*s != '\0'))
				s++;
		}
		while ((*s == c) && (c != '\0'))
			s++;
	}
	return (arr_size);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		i;

	if (!s)
		return (NULL);
	splitted = (char **)malloc((sizeof(char *) * (spt_size(s, c) + 1)));
	if (!splitted)
		return (NULL);
	i = -1;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if ((*s != c) && (*s != '\0'))
		{
			if (!(malloc_str(splitted, spt_len(s, c), ++i)))
				return (NULL);
			ft_strlcpy(splitted[i], s, spt_len(s, c) + 1);
			while ((*s != c) && (*s != '\0'))
				s++;
		}
	}
	splitted[++i] = NULL;
	return (splitted);
}
