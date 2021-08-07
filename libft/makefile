NAME = libft.a

SRCS = ft_atoi.c ft_islower.c ft_memmove.c ft_strdup.c ft_strrchr.c \
ft_isprint.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_bzero.c \
ft_isupper.c ft_putchar_fd.c ft_strlcat.c ft_substr.c \
ft_calloc.c ft_itoa.c ft_putendl_fd.c ft_strlcpy.c ft_tolower.c \
ft_isalnum.c ft_memccpy.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c \
ft_isalpha.c ft_memchr.c ft_putstr_fd.c  ft_strmapi.c \
ft_isascii.c ft_memcmp.c ft_split.c ft_strncmp.c \
ft_isdigit.c ft_memcpy.c ft_strchr.c ft_strnstr.c 

BNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
      ft_lstiter.c ft_lstmap.c

HEADERS = libft.h

OPTION = -I ${HEADERS}

OBJS = ${SRCS:.c=.o}

BNSOBJ = ${BNS:.c=.o}

ALLOBJ = 

CC	= gcc

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC}  ${CFLAGS} -c $< -o ${<:.c=.o}

RM = rm -f

all:	${NAME} 
	
$(NAME): ${OBJS}
	ar rc ${NAME} ${OBJS}
	ranlib $(NAME)


clean:
		${RM} ${OBJS} ${BNSOBJ}

fclean:	clean
		${RM} ${NAME}

re: fclean all

bonus: fclean ${BNSOBJ} ${OBJS}
	ar rc ${NAME} ${OBJS} ${BNSOBJ}

.PHONY:	clean fclean all re
