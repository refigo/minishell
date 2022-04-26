/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_and_cmd_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:05:57 by mgo               #+#    #+#             */
/*   Updated: 2022/04/20 15:05:59 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_cmd_args(t_exec_data *data, t_cmda_list *cmd_area, t_ast *node)
{
	t_ast	*tmp;
	int		cnt;

	tmp = node;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		tmp = tmp->right;
	}
	cmd_area->cmd_args = ft_calloc(cnt + 1, sizeof(char *));
	ft_assert(cmd_area->cmd_args != NULL, "malloc failed in set_cmd_args");
	cnt = -1;
	tmp = node;
	while (tmp)
	{
		(cmd_area->cmd_args)[++cnt] = ft_strdup(tmp->token);
		ft_assert(cmd_area->cmd_args[cnt] != NULL, \
			"ft_strdup failed in set_cmd_args");
		tmp = tmp->right;
	}
}

static void	set_exec(t_exec_data *data, t_cmda_list *cmd_area, char **path)
{
	char	*cmd;
	int		i;

	cmd = cmd_area->exec;
	i = -1;
	while (path && path[++i])
	{
		cmd_area->exec = ft_strjoin(path[i], cmd);
		ft_assert(cmd_area->exec != NULL, "ft_strjoin failed in set_exec");
		if (access(cmd_area->exec, X_OK) == SUCCESS)
			break ;
		free(cmd_area->exec);
		cmd_area->exec = NULL;
	}
	if (cmd_area->exec == NULL)
	{
		cmd_area->exec = ft_strdup(cmd);
		ft_assert(cmd_area->exec != NULL, "ft_strdup failed in set_exec");
	}
}

static void	add_slash_to_path(t_exec_data *data, char **path)
{
	char	*buf;
	int		len_path;
	int		i;

	if (path == NULL)
		return ;
	i = -1;
	while (path[++i])
	{
		len_path = ft_strlen(path[i]);
		buf = (char *)ft_calloc(1, len_path + 2);
		ft_assert(buf != NULL, "Error: malloc failed in add_slash_to_path");
		ft_memmove(buf, path[i], len_path);
		buf[len_path] = '/';
		free(path[i]);
		path[i] = buf;
	}
}

void	set_exec_and_cmd_args(t_exec_data *data, t_ast *node, \
	t_cmda_list *cmd_area)
{
	t_info		*info_addr;
	t_env_node	*env_path;
	char		**path;

	ft_assert(node->type == TOK_TYPE_CMD, \
		"Error: not cmd type in set_exec_and_cmd_args func");
	info_addr = (t_info *)data->info;
	data->num_cmds += 1;
	cmd_area->exec = node->token;
	env_path = get_env_node(info_addr->unordered_env, "PATH");
	path = ft_split(env_path->value, ':');
	add_slash_to_path(data, path);
	set_exec(data, cmd_area, path);
	mgo_free_2ptr(path);
	set_cmd_args(data, cmd_area, node);
}
