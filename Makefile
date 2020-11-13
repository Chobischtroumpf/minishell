# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:53:12 by adorigo           #+#    #+#              #
#    Updated: 2020/11/13 16:23:41 by adorigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = srcs
SRC_NAME =	cmd_add_rdir.c	\
			cmd_parser_1.c	\
			cmd_parser_2.c	\
			get_static.c	\
			lexing.c		\
			minishell.c		\
			utils.c			\
			env.c			\
			env2.c			\
			exec_cmd.c		\
			bltin_echo.c	\
			bltin_exit.c	\
			bltin_pwd.c		\
			bltin_env.c		\
			bltin_unset.c	\
			bltin_export.c	\
			bltin_cd.c 		\
			exec_external.c	\
			errors.c		\
			errors2.c		\
			line_handle.c	\
			redirections.c	\
			quit.c			\
			exit.c			\
			dollar.c		\
			brackets.c		\
			free.c			\
			shlvl.c			


OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I include -I libft/includes
LDFLAGS = -L libft
LDLIBS = -lft 

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: libft_bonus $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "Compilation of minishell:	\033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -pv $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< $(CFLAGS) -o $@

libft:
	@make -C libft

libft_bonus:
	@make -C libft bonus

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

clean_libft:
	@make -C libft clean

clean_minishell:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean_libft:
	@make -C libft fclean

fclean_minishell:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)

fclean: fclean_minishell fclean_libft

re: fclean all

re_minishell: fclean_minishell $(NAME)

re_libft:
	@make -C libft re

bonus: all

.PHONY: all clean fclean re libft clean_minishell clean_libft fclean_minishell fclean_libft re_minishell re_libft