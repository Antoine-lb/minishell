# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 11:56:06 by ale-baux          #+#    #+#              #
#    Updated: 2020/03/12 18:16:58 by ale-baux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = minishell

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

DIR_S = sources

DIR_O = temporary

HEADER = includes

SOURCES = main.c \
		  bi_env.c \
		  bi_export.c \
		  bi_unset.c \
          bi_echo.c \
          bi_cd.c \
		  variable.c \
		command_return.c \
		  command_parser.c \
		  command.c \
		  initialization.c \
		  parser_tools.c \
		  parser.c \
		  parsing_filter.c \
		  get_env_var_value.c \
		  argument.c \
		  get_path_from_env.c \
		  signal_handling.c \
		  execute_commands.c \
		  dup_env.c \
		  sort.c \
		  free_2d_array.c \
		  is_same_var.c \
		  bi_pwd.c \
		  get_fd_in_and_out.c \
		  exec_child.c \
		  bi_exit.c \
		  dup_and_add_env.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: temporary $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(FLAGS)  -o $@ $^ -L $(LIBFT) -lft

temporary:
	@mkdir -p temporary

$(DIR_O)/%.o: $(DIR_S)/%.c
	@$(CC) $(FLAGS) -I $(HEADER) -c -o $@ $<

norme:
	@echo
	norminette ./$(LIBFT)
	@echo
	norminette ./$(HEADER)
	@echo
	norminette ./$(DIR_S)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all
	
.PHONY: temporary, norme, clean
