#ifndef TOKNIZER_H
# define TOKNIZER_H

# include "libft.h"

typedef enum e_tok_type
{
	TOK_TYPE_CMD,
	TOK_TYPE_ARG,
	TOK_TYPE_PIPE,
	TOK_TYPE_REDIR,
	TOK_TYPE_FILE,
	TOK_TYPE_STR,
	TOK_TYPE_UNDEFINE
}	t_tok_type;

typedef enum e_flag
{
	FLAG_CMD = 0,
	FLAG_REDIR
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
t_tok_list	*tokenizer(char *input);
void		lexer(t_tok_list *tok_list);
void		remove_quote(char *dest, char *src);
int			calc_quote(char *input);
char		*jump_quotes(char *cur, int c);
#endif

