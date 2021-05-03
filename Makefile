# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chpl <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:45:13 by chpl              #+#    #+#              #
#    Updated: 2021/03/24 10:37:33 by chpl             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/
DIR_S = srcs
DIR_O = objs
INCLUDES = -I includes/ -I ${LIBFT}
CC = clang
LIBS = -L libft/ -lft -lncurses -lX11
CFLAGS	= -Wall -Wextra -Werror
SOURCES =  srcs/main.c \
	   srcs/builtins/builtins.c \
	   srcs/builtins/nsh_cd.c \
	   srcs/builtins/nsh_echo.c \
	   srcs/builtins/nsh_env.c \
	   srcs/builtins/nsh_exit.c \
	   srcs/builtins/nsh_export.c \
	   srcs/builtins/nsh_pwd.c \
	   srcs/builtins/nsh_unset.c \
	   srcs/lexer/lexer.c \
	   srcs/lexer/count.c \
	   srcs/lexer/set_len.c \
	   srcs/exec.c \
	   srcs/expand_word.c \
	   srcs/utils.c \
	   srcs/term.c \
	   srcs/env.c \
	   srcs/signals.c \
	   srcs/loop.c \
	   srcs/write_dot.c \
	   srcs/parser/parser.c \
	   srcs/parser/astree.c \
	   srcs/prompt/prompt.c \
	   srcs/inputs/ascii.c \
	   srcs/inputs/clear.c \
	   srcs/inputs/cursor.c \
	   srcs/inputs/get_input.c \
	   srcs/inputs/his_navigate.c \
	   srcs/inputs/his_new.c \
	   srcs/inputs/history.c \
	   srcs/inputs/arrows.c \
	   srcs/inputs/utf.c

OBJS	= ${SOURCES:.c=.o}

.c.o:
	${CC} ${CFLAGS} ${GNLBUFF} -c $< -o ${<:.c=.o} ${INCLUDES}
	mv ${<:.c=.o} ${DIR_O}

all : $(NAME)

${NAME}: ${OBJS} ft 
	
	${CC} ${CFLAGS} ${INCLUDES} ${DIR_O}/*.o ${LIBS} -o ${NAME}

ft:
	@make -C libft

graph:
	dot -Tjpg graph.dot > graph.jpg

clean :
	@rm -f $(DIR_O)/*.o
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY:	clean fclean all re mlx ft
