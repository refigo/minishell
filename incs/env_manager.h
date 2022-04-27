/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:40:37 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:47:13 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H

# define BIG_SIZE (4096)

# include <stdio.h>

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
	int			size;
}	t_env_list;

t_env_node	*new_node(char *key, char *value);
int			init_env_list(t_env_list *list);
void		del_env_list(t_env_list **env_list);
int			env_insert_first(t_env_list *list, t_env_node *node);
int			env_insert_end(t_env_list *list, t_env_node *node);
int			env_insert_mid(t_env_list *list, t_env_node *node, int n);
int			env_insert_asc(t_env_list *list, t_env_node *node);
void		env_insert(t_env_list *list, char *key, char *value);
void		env_insert_attach_value(t_env_list *list, char *key, char *value);
void		env_remove_first(t_env_list *list);
void		env_remove_end(t_env_list *list);
void		env_remove(t_env_list *list, char *key);
t_env_node	*get_env_node(t_env_list *list, char *key);
t_env_list	*env_sort_copy_env(t_env_list *list);
t_env_node	*copy_node_unlink(t_env_node *node);
char		**convert_env_char_d_ptr(t_env_list *list);
char		*get_env_value_not_malloc(t_env_list *list, char *key);
void		env_modify_value_not_malloc(t_env_list *list, \
										char *key, char *value);
void		print_env(t_env_list *list, char *form, char *except);

#endif
