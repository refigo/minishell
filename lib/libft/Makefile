# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 10:22:57 by mgo               #+#    #+#              #
#    Updated: 2022/02/15 14:49:41 by mgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
AR			=	ar
AR_FLAG		=	-crs
RM			=	rm
RM_FLAG		=	-rf

HDR_DIR		=	./includes/
HDR_LIST	=	libft.h \
				get_next_line.h
INC_LINK	=	-I./includes/

SRC_DIR		=	./sources/
SRC_LIST	=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				get_next_line.c \
				get_next_line_utils.c \
				mgo_free.c \
				mgo_strcmp.c
SRCS		=	$(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR		=	./objects/
OBJ_LIST	=	$(SRC_LIST:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ_LIST))

$(NAME)	:	$(OBJS)
	@$(AR) $(AR_FLAG) $@ $^

$(OBJ_DIR)%.o		:	$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_LINK) -c $< -o $@

all 	:	$(NAME)

clean	:
	@$(RM) $(RM_FLAG) $(OBJ_DIR)

fclean	:	clean
	@$(RM) $(RM_FLAG) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
