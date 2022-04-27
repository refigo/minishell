/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:06 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:42:07 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 해줘야 하는것
	1. envp에 있는 모든 정보
	2. PS1 수정
	3. SHLVL 수정 (SHLVL + 1)
	!하위 내용 일단 무시
	4. 예약변수
	5. 위치 매개 변수
	6. 특수 매개 변수
*/

char	*ft_strndup(char *str, int n)
{
	char	*ret;

	ret = ft_calloc(1, sizeof(char) * (n + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, str, n + 1);
	return (ret);
}

void	make_env_list(t_env_list *env, int argc, char **argv, char **envp)
{
	char		*value;
	t_env_node	*temp;
	char		*temp_str;

	while (*envp != NULL)
	{
		value = ft_strchr(*envp, '=');
		env_insert_end(env, \
		new_node(ft_substr(*envp, 0, value - *envp), \
		ft_strdup(value + 1)));
		++envp;
	}
	temp = get_env_node(env, "SHLVL");
	if (temp != NULL)
	{
		temp_str = ft_itoa(ft_atoi(temp->value) + 1);
		free(temp->value);
		temp->value = temp_str;
	}
	env_insert_end(env, \
		new_node(ft_strdup("?"), ft_strdup("0")));
}
