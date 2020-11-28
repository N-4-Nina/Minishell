# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chpl <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:45:13 by chpl              #+#    #+#              #
#    Updated: 2020/11/24 10:20:58 by chpl             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/
DIR_S = srcs
DIR_O = objs
INCLUDES = -I includes/ -I ${LIBFT}
CC = clang
LIBS = -L libft/ -lft
CFLAGS	= -Wall -Wextra -Werror
GNLBUFF = -D BUFFER_SIZE=100
SOURCES =  srcs/main.c \
	   srcs/builtins.c \
	   srcs/utils.c \
	   srcs/env.c \
	srcs/get_next_line.c

OBJS	= ${SOURCES:.c=.o}

.c.o:
	${CC} ${CFLAGS} ${GNLBUFF} -c $< -o ${<:.c=.o} ${INCLUDES}

all : $(NAME)

${NAME}: ${OBJS} ft 
	${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIBS} -o ${NAME}

ft:
	@make -C libft

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/*.h
	@mkdir -p objs
	@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean :
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY:	clean fclean all re mlx ft
