# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nathan <nathan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:53:12 by adorigo           #+#    #+#              #
#    Updated: 2021/01/08 19:38:33 by nathan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


###############################
### LOADING BAR BY VGOLDMAN ###
###############################
TOTAL = $(shell find srcs -iname  "*.c" | wc -l | bc)
O_COUNT = 0
COUNT = 0
define update
	$(eval O_COUNT := $(shell find objs -iname "*.o" 2> /dev/null | wc -l | bc))
	printf "\r["
	printf "=%.0s" $(shell seq 0 ${O_COUNT})
	printf ">"
	$(eval COUNT := $(shell echo ${TOTAL} - ${O_COUNT} | bc))
	printf "%${COUNT}s" "]"
endef
########################################

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
			files.c					\
			pipe.c

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I include -I libft/includes
LDFLAGS = -L libft #-fsanitize=address
LDLIBS = -lft 

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

TICK = \342\234\224
RE = \342\231\272
TRASH = \360\237\227\221

default:
	@make -s all

all: libft $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "\033[32;1m\rMinishell by adorigo & ncolin compiled ${TICK}          \033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< $(CFLAGS) -o $@
	@$(call update)

libft:
	@make -s -C libft

libft_bonus:
	@make -s -C libft bonus
	
.SILENT:clean

clean:
	@make -s -C libft clean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[32;1m\rDirectory cleaned ${TRASH}          \033[0m"

clean_libft:
	@make -s -C libft clean

clean_minishell:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean_libft:
	@make -s -C libft fclean

fclean_minishell:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	

fclean: fclean_minishell fclean_libft
	@echo "\033[32;1m\rDirectory fully cleaned ${TRASH} ${TRASH} ${TRASH}          \033[0m"

re: 
	@echo "\033[32;1m\rMinishell recompiling ${RE}          \033[0m"
	@make -s fclean 
	@make -s all
	

re_minishell: fclean_minishell $(NAME)

re_libft:
	@make -s -C libft re

bonus: all

.PHONY: all clean fclean re libft clean_minishell clean_libft fclean_minishell fclean_libft re_minishell re_libft