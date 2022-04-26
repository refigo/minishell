#include "minishell.h"

static void	add_env(char *key_value, t_env_list *env)
{
	char		*value;
	char		*temp_value;
	t_env_node	*temp;

	value = ft_strchr(key_value, '=');
	if (value == NULL)
	{
		if (get_env_node(env, key_value) == NULL)
			env_insert_end(env, \
			new_node(ft_strdup(key_value), ft_strdup("")));
	}
	else
	{
		if (*(value - 1) == '+')
		{
			*(value - 1) = '\0';
			*value++ = '\0';
		}
		else
			*(value++) = '\0';
		temp = get_env_node(env, key_value);
		if (temp == NULL)
		{
			env_insert_end(env, \
			new_node(ft_strdup(key_value), ft_strdup("")));
		}
		else
		{

		}
	}
}

int	builtin_export(char **args, t_env_list *env)
{
	if (*(args + 1) == NULL)
		print_env(env, "declare -x %s=\"%s\"\n", "?");
}
