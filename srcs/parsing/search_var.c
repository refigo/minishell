#include "minishell.h"

static char	*dup_replace_var(t_env_list *list, char **start, char *end, bool escape)
{
	char		*temp;
	t_env_node	*node;

	if (escape == true)
	{
		--(*start);
		return (ft_strdup("$"));
	}
	temp = ft_substr(*start, 1, end - *start - 1);
	node = get_env_node(list, temp);
	if (temp != NULL)
		free(temp);
	if (node == NULL)
		return (ft_strdup(""));
	return (ft_strdup(node->value));
}

static char	*expand_input(char **input, char *var_start, t_env_list *env, bool escape)
{
	char	*var_end;
	char	*replace_var;
	char	*ret;
	int		replace_var_len;

	var_end = var_start + 1;
	while (*var_end && ft_strchr("\"\'<>| $", *var_end) == NULL)
		++var_end;
	replace_var = dup_replace_var(env, &var_start, var_end, escape);
	ft_assert(replace_var != NULL, "ERROR : leak resource in expand_input()");
	replace_var_len = ft_strlen(*input) - (var_end - var_start + 1) \
	+ ft_strlen(replace_var);
	ret = ft_calloc(1, sizeof(char) * (replace_var_len + 1));
	ft_assert(ret != NULL, "ERROR : leak resource in expand_input()");
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

/*
	개선해야 할점
	$$형식으로 들어오면 프로세스 id를 반환해야한다
	$만 들어오면 \$와 동일하게 처리해야한다.
	sd
*/
void	search_var(char **input, t_env_list *env, bool quote_flag)
{
	char	*iter;

	if (*input == NULL)
		return ;
	iter = *input;
	while (*iter != '\0')
	{
		if (*iter == '\"' && (iter == *input || *(iter - 1) != '\\'))
			quote_flag = !quote_flag;
		else if (*iter == '\'' && quote_flag == false)
			iter = ft_strchr(iter + 1, '\'');
		else if (*iter == '<' && *(iter + 1) == '<' && quote_flag == false)
			iter = jump_word(iter += 2);
		else if (*iter == '$')
		{
			if (iter != *input && *(iter - 1) == '\\')
				iter = expand_input(input, iter, env, true);
			else
				iter = expand_input(input, iter, env, false);
			continue;
		}
		++iter;
	}
	return ;
}
