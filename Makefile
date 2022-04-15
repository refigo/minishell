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

NAME		=	mgoshell

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		+=	-fsanitize=address -g
RM			=	rm -rf

INC_LINK	=	-I./incs/ -I./lib/libft/includes/
LIBFT		=	-L./lib/libft -lft

SRC_PATH	=	./srcs/
OBJ_PATH	=	./obj/

SRC_LIST	=	main.c
SRC			=	$(addprefix $(SRC_PATH), $(SRC_LIST))

OBJ_LIST	=	$(SRC_LIST:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_LIST))

$(OBJ_PATH)%.o	:	$(SRC_PATH)$(DIR_MAN)%.c
	@echo $(YELLOW) "Compling...\t" $< $(ENDCOLOR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_LINK) -c $< -o $@

$(NAME)	:	$(OBJ) libft
	@echo $(GREEN) "Source files are compiled!\n" $(ENDCOLOR)
	@echo $(YELLOW) "Building $(NAME)..."
	@$(CC) $(CFLAGS) $(INC_LINK) $(LIBFT) $(OBJ) -o $(NAME)
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
