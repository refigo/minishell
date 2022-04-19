# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 14:54:02 by mgo               #+#    #+#              #
#    Updated: 2022/04/01 16:53:17 by mgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[0;33m"
WHITE		=	"\033[0;37m"
BRED		=	"\033[1;31m"
BGREEN		=	"\033[1;32m"
BYELLOW		=	"\033[1;33m"
BWHITE		=	"\033[1;37m"
ENDCOLOR	=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

NAME		=	minishell

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		+=	-fsanitize=address -g
RM			=	rm -rf

INC_LINK	=	-I./incs/  

FT_LINK		=	-I./lib/libft				# bson
#FT_LINK	=	-I./lib/libft/includes/		# mgo(not include)
LIBFT		=	-L./lib/libft -lft

#RL_LINK	=	-I/usr/local/opt/readline/include/					# bson
RL_LINK		=	-I/goinfre/mgo/.brew/opt/readline/include/			# mgo
#READLINE	=	-L/usr/local/opt/readline/lib/ -lreadline			# bson
READLINE	=	-L/goinfre/mgo/.brew/opt/readline/lib/ -lreadline	# mgo

SRC_PATH	=	./srcs/
DIR_PARS	=	parsing/
DIR_EXEC	=	execution/
OBJ_PATH	=	./objs/

SRC_LIST	=	main.c \
				$(DIR_PARS)env_manager.c \
				$(DIR_PARS)env_search.c \
				$(DIR_PARS)env_insert.c \
				$(DIR_PARS)make_env_list.c \
				$(DIR_PARS)shell_info.c \
				$(DIR_PARS)check_input.c \
				$(DIR_PARS)tokenizer.c \
				$(DIR_PARS)tok_insert.c \
				$(DIR_PARS)tok_modify.c \
				$(DIR_PARS)tok_init.c \
				$(DIR_PARS)search_var.c \
				$(DIR_PARS)lexer.c \
				$(DIR_PARS)remove_quotes.c \
				$(DIR_PARS)ast_manager.c \
				$(DIR_PARS)ast_insert.c \
				$(DIR_PARS)parser.c \
				$(DIR_PARS)check_syntax.c
SRC			=	$(addprefix $(SRC_PATH), $(SRC_LIST))

OBJ_LIST	=	$(SRC_LIST:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_LIST))

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
	@echo $(YELLOW) "Compling...\t" $< $(ENDCOLOR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)$(DIR_PARS) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_LINK) $(FT_LINK) $(RL_LINK) -c $< -o $@

$(NAME)	:	$(OBJ) libft
	@echo $(GREEN) "Source files are compiled!\n" $(ENDCOLOR)
	@echo $(YELLOW) "Building $(NAME)..."
	@$(CC) $(CFLAGS) $(INC_LINK) $(FT_LINK) $(RL_LINK) $(LIBFT) $(READLINE) $(OBJ) -o $(NAME)
	@echo $(GREEN) "$(NAME) is created!\n" $(ENDCOLOR)

libft	:
	@make -C ./lib/libft all

all		:	$(NAME)

bonus	:	$(NAME)

clean	:
	@echo $(YELLOW) "Cleaning object files..." $(ENDCOLOR)
	@make -C ./lib/libft clean
	@$(RM) $(OBJ_PATH)
	@echo $(RED) "Object files are cleaned!\n" $(ENDCOLOR)

fclean	: clean
	@echo $(YELLOW) "Removing $(NAME)..." $(ENDCOLOR)
	@make -C ./lib/libft fclean
	@$(RM) $(OBJ_PATH) $(NAME)
	@echo $(RED) "$(NAME) is removed!\n" $(ENDCOLOR)

re		:	fclean all

.PHONY	:	all bonus clean fclean re
