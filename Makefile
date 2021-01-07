# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:53:12 by adorigo           #+#    #+#              #
#    Updated: 2021/01/04 14:49:04 by ncolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = srcs
SRC_NAME =	cmd_add_rdir.c			\
			cmd_parser_1.c			\
			cmd_parser_2.c			\
			get_static.c			\
			lexing.c				\
			minishell.c				\
			utils.c					\
			utils2.c				\
			utils3.c				\
			utils4.c				\
			env.c					\
			env2.c					\
			exec_cmd.c				\
			bltin_echo.c			\
			bltin_exit.c			\
			bltin_pwd.c				\
			bltin_env.c				\
			bltin_unset.c			\
			bltin_export.c			\
			bltin_cd.c 				\
			exec_external.c			\
			errors.c				\
			errors2.c				\
			errors3.c				\
			errors4.c				\
			line_handle.c			\
			redirections.c			\
			quit.c					\
			exit.c					\
			dollar.c				\
			dollar2.c				\
			brackets.c				\
			free.c					\
			shlvl.c					\
			ft_split_empty.c		\
			ft_split_skip_quotes.c	\
			files.c         \
      pipe.c



OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I include -I libft/includes
LDFLAGS = -L libft #-fsanitize=address
LDLIBS = -lft 

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: libft $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "Compilation of minishell:	\033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -pv $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< $(CFLAGS) -o $@

libft:
	@make -C libft<<<<<<< pipe
17
 
SRC_NAME =  cmd_add_rdir.c  \
18
 
      cmd_parser_1.c  \
19
 
      cmd_parser_2.c  \
20
 
      get_static.c  \
21
 
      lexing.c    \
22
 
      minishell.c   \
23
 
      utils.c     \
24
 
      utils2.c    \
25
 
      utils3.c    \
26
 
      utils4.c    \
27
 
      env.c     \
28
 
      env2.c      \
29
 
      exec_cmd.c    \
30
 
      bltin_echo.c  \
31
 
      bltin_exit.c  \
32
 
      bltin_pwd.c   \
33
 
      bltin_env.c   \
34
 
      bltin_unset.c \
35
 
      bltin_export.c  \
36
 
      bltin_cd.c    \
37
 
      exec_external.c \
38
 
      errors.c    \
39
 
      errors2.c   \
40
 
      errors3.c   \
41
 
      errors4.c   \
42
 
      line_handle.c \
43
 
      redirections.c  \
44
 
      quit.c      \
45
 
      exit.c      \
46
 
      dollar.c    \
47
 
      dollar2.c   \
48
 
      brackets.c    \
49
 
      free.c      \
50
 
      shlvl.c     \
51
 
      files.c     \
52
 
      pipe.c
53
 
=======

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