/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:21 by bson              #+#    #+#             */
/*   Updated: 2022/04/30 14:01:23 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_vaild_env(char *key)
{
	char	*temp;
	int		cnt;

	temp = ft_strchr(key, '=');
	if (temp == key)
		return (0);
	if (temp == NULL)
		cnt = ft_strlen(key);
	else
		cnt = temp - key;
	while (*key != '\0' && cnt--)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (0);
		++key;
	}
	return (1);
}

static void	separate_pair(char **key, char **value, char *key_value)
{
	char	*m_key;
	char	*m_value;
	char	*wall;

	m_value = ft_strchr(key_value, '=');
	if (m_value == NULL)
	{
		m_value = ft_strdup("");
		m_key = ft_strdup(key_value);
		ft_assert(m_key != NULL && m_value != NULL, \
		"leak resource in separat_pair()");
	}
	else
	{
		wall = m_value;
		if (*(m_value - 1) == '+')
			--wall;
		m_key = ft_substr(key_value, 0, wall - key_value);
		m_value = ft_strdup(++m_value);
		ft_assert(m_key != NULL && m_value != NULL, \
		"leak resource in separat_pair()");
	}
	*key = m_key;
	*value = m_value;
}

static void	add_env(char *key, char *value, t_env_list *env, char *arg)
{
	char		*temp;

	temp = ft_strchr(arg, '=');
	if (temp != NULL && *(temp - 1) == '+')
		env_insert_attach_value(env, key, value);
	else
		env_insert(env, key, value);
}

int	builtin_export(char **args, t_env_list *env)
{
	t_env_list	*env_asc;
	char		*key;
	char		*value;

	if (*(args + 1) == NULL)
	{
		env_asc = env_sort_copy_env(env);
		print_env(env_asc, "declare -x %s=\"%s\"\n", "?", true);
		del_env_list(&env_asc);
		return (0);
	}
	while (*(++args) != NULL)
	{
		if (is_vaild_env(*args) == false)
		{
			ft_putstr_fd("mbsh: export: `", STDERR_FILENO);
			ft_putstr_fd(*args, STDERR_FILENO);
			ft_putendl_fd("': Not a valid identifier", STDERR_FILENO);
			return (1);
		}
		separate_pair(&key, &value, *args);
		add_env(key, value, env, *args);
	}
	return (0);
}
