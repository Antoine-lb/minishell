NAME = minishell

SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

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
