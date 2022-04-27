/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:40:51 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:40:52 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKNIZER_H
# define TOKNIZER_H

typedef enum e_tok_type
{
	TOK_TYPE_PIPE,
	TOK_TYPE_REDIR,
	TOK_TYPE_FILE,
	TOK_TYPE_CMD,
	TOK_TYPE_ARG,
	TOK_TYPE_UNDEFINE
}	t_tok_type;

typedef enum e_flag
{
	FLAG_CMD = 0,
	FLAG_REDIR,
	FLAG_PIPE
}	t_flag;

typedef struct s_tok
{
	char			*token;
	t_tok_type		type;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

typedef struct s_tok_list
{
	t_tok	*head;
	t_tok	*tail;
	int		size;
}	t_tok_list;

t_tok		*new_token(char *tok);
t_tok_list	*new_tok_list(void);
void		insert_tok_end(t_tok_list *list, t_tok *tok);
void		remove_token_list(t_tok_list **list);
t_tok_list	*tokenizer(char *input);
void		remove_quotes(t_tok *node);
char		*jump_quotes(char *cur, int c, int escape);
int			check_syntax(t_tok_list *list);
int			lexer(t_tok_list *tok_list);
#endif
