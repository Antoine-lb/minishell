NAME = minishell

SRCS = main.c \
	   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	   libft/ft_strrchr.c libft/ft_strlen.c libft/ft_putstr_fd.c libft/ft_putchar_fd.c libft/ft_strjoin.c libft/ft_substr.c \
	   libft/ft_strdup.c

OBJS = ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
		@gcc ${SRCS} -o ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

run:	all

norm:
		norminette ${SRCS}
