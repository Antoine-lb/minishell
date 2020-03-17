# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 08:37:51 by gsharony          #+#    #+#              #
#    Updated: 2020/03/13 15:40:55 by guysharon        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

DIR			= ./

SRCS		= ${DIR}ft_putchar_fd.c ${DIR}ft_putstr_fd.c ${DIR}ft_putendl_fd.c ${DIR}ft_putnbr_fd.c ${DIR}ft_itoa.c ${DIR}ft_atoi.c ${DIR}ft_bzero.c ${DIR}ft_calloc.c ${DIR}ft_isalnum.c ${DIR}ft_isalpha.c ${DIR}ft_isascii.c ${DIR}ft_isdigit.c ${DIR}ft_isprint.c ${DIR}ft_memccpy.c ${DIR}ft_memchr.c ${DIR}ft_memcmp.c ${DIR}ft_memcpy.c ${DIR}ft_memmove.c ${DIR}ft_memset.c ${DIR}ft_strchr.c ${DIR}ft_strdup.c ${DIR}ft_strjoin.c ${DIR}ft_strlcat.c ${DIR}ft_strlcpy.c ${DIR}ft_strlen.c ${DIR}ft_strncmp.c ${DIR}ft_strnstr.c ${DIR}ft_strrchr.c ${DIR}ft_strtrim.c ${DIR}ft_substr.c ${DIR}ft_tolower.c ${DIR}ft_toupper.c ${DIR}ft_itoa.c ${DIR}ft_strmapi.c ${DIR}ft_strcpy.c ${DIR}ft_split.c ${DIR}get_next_line.c ${DIR}get_next_line_utils.c ${DIR}ft_strcmp.c ${DIR}ft_lstnew_bonus.c ${DIR}ft_lstmap_bonus.c ${DIR}ft_lstiter_bonus.c ${DIR}ft_lstclear_bonus.c ${DIR}ft_lstdelone_bonus.c ${DIR}ft_lstadd_back_bonus.c ${DIR}ft_lstlast_bonus.c ${DIR}ft_lstsize_bonus.c ${DIR}ft_lstadd_front_bonus.c ${DIR}ft_getnext.c ${DIR}ft_getnnext.c ${DIR}ft_stripslashes.c ${DIR}ft_includes.c

OBJECTS		= ${SRCS:.c=.o}

INCLUDES	= ./

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -I ${INCLUDES}

.c.o:
			${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o ${<:.c=.o}

all: 		${NAME}

$(NAME):	${OBJECTS}
			ar rc ${NAME} ${OBJECTS}

clean:
			${RM} ${OBJECTS}

re:			fclean all

fclean:		clean
			${RM} ${NAME}

.PHONY:		all clean fclean
