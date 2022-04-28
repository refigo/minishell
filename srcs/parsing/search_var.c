/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:15 by bson              #+#    #+#             */
/*   Updated: 2022/04/29 00:24:14 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_replace_var(t_env_list *list, char **start, char *end)
{
	char		*temp;
	t_env_node	*node;

	temp = ft_substr(*start, 1, end - *start - 1);
	node = get_env_node(list, temp);
	if (temp != NULL)
		free(temp);
	if (node == NULL)
		return (ft_strdup(""));
	return (ft_strdup(node->value));
}

static char	*expand_input(char **input, char *var_start, t_env_list *env)
{
	char	*var_end;
	char	*replace_var;
	char	*ret;
	int		replace_var_len;

	var_end = var_start + 1;
	while (*var_end && ft_strchr("\"\'<>| $", *var_end) == NULL)
		++var_end;
	replace_var = dup_replace_var(env, &var_start, var_end);
	ft_assert(replace_var != NULL, "leak resource in expand_input()");
	replace_var_len = ft_strlen(*input) - (var_end - var_start) \
	+ ft_strlen(replace_var);
	ret = ft_calloc(1, sizeof(char) * (replace_var_len + 1));
	ft_assert(ret != NULL, "leak resource in expand_input()");
	ft_strncpy(ret, *input, var_start - *input);
	ft_strncat(ret, replace_var, replace_var_len);
	ft_strncat(ret, var_end, ft_strlen(var_end));
	replace_var_len = (var_start - *input) + ft_strlen(replace_var);
	free(replace_var);
	free(*input);
	*input = ret;
	return (ret + replace_var_len);
}

static char	*jump_word(char *input)
{
	while (*input && ft_isspace(*input) == true)
		++input;
	while (*input && ft_isspace(*input) == false)
		++input;
	return (input);
}

void	search_var(char **input, t_env_list *env, bool quote_flag)
{
	char	*iter;

	if (*input == NULL)
		return ;
	iter = *input;
	while (*iter != '\0')
	{
		if (*iter == '\"' && (iter == *input || *(iter - 1) != '\\') && ++iter)
			quote_flag = !quote_flag;
		else if (*iter == '\'' && quote_flag == false && \
				(iter == *input || *(iter - 1) != '\\'))
			iter = ft_strchr(iter + 1, '\'') + 1;
		else if (*iter == '<' && *(iter + 1) == '<' && quote_flag == false)
			iter = jump_word(iter + 2);
		else if (*iter == '$' && (iter == *input || *(iter - 1) != '\\'))
			iter = expand_input(input, iter, env);
		else
			++iter;
	}
	return ;
}
