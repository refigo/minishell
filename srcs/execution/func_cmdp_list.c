/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cmdp_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:24:25 by mgo               #+#    #+#             */
/*   Updated: 2022/04/20 09:24:26 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_cmd_area(t_cmda_list **cmd_areas, t_cmda_list *new)
{
	t_cmda_list	*tmp;

	if (cmd_areas == NULL || new == NULL)
	{
		printf("cmd_areas == NULL || new == NULL in add_new_redir\n");
		exit(1);
	}
	if (*cmd_areas == NULL)
		*cmd_areas = new;
	else
	{
		tmp = *cmd_areas;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (TRUE);
}
