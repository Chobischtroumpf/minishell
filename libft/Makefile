# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:53:12 by adorigo           #+#    #+#              #
#    Updated: 2020/05/14 10:28:23 by adorigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FOLDER = ft_printf

CFLAGS = -Wall -Wextra -Werror -I./includes -c

SRCS = ft_memset.c ft_strlast.c ft_memcpy.c ft_memccpy.c ft_memmove.c	\
		ft_memchr.c	ft_memcmp.c	ft_strnstr.c ft_isascii.c ft_substr.c	\
		ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c	\
		ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c	\
		ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c	\
		ft_strjoin.c ft_strnbr.c ft_split.c ft_strmapi.c ft_strnjoin.c	\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c	\
		ft_putchar.c ft_putendl.c ft_strcmp.c ft_strnew.c ft_strfree.c	\
		ft_putstr.c ft_putnbr.c ft_isspace.c ft_numlen.c ft_strcat.c	\
		ft_strcpy.c ft_strncat.c ft_strncpy.c ft_strndup.c ft_strstr.c	\
		ft_strtrim.c ft_utoa_base.c ft_itoa_base.c ft_itoa.c ft_bzero.c	\
		get_next_line.c ft_haschr.c ft_printf.c

SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c 	\
		ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c 	\
		ft_lstiter_bonus.c ft_lstclear_bonus.c

SRCS_LIST_FT_PRINTF = aux_check.c aux_pl.c aux_print_and_count.c		\
				print_c.c print_d.c print_p.c print_percent.c print_s.c	\
				print_u.c print_x.c 

SRCS_FT_PRINTF = $(addprefix ${FOLDER}/, ${SRCS_LIST_FT_PRINTF})

OBJECTS = $(SRCS:%.c=%.o)

OBJECTS_B = $(SRCS_B:%.c=%.o)

OBJECTS_FT_PRINTF = $(SRCS_LIST_FT_PRINTF:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJECTS) $(OBJECTS_FT_PRINTF)
		@ar rcs $(NAME) $(OBJECTS) $(OBJECTS_FT_PRINTF)

$(OBJECTS) : $(SRCS)
		gcc $(CFLAGS) $(SRCS)

$(OBJECTS_FT_PRINTF) : $(SRCS_FT_PRINTF)
		gcc $(CFLAGS) $(SRCS_FT_PRINTF)

$(OBJECTS_B) : $(SRCS_B)
		gcc $(CFLAGS) $(SRCS_B)

bonus : fclean $(OBJECTS) $(OBJECTS_B)
	@ar rcs libft.a $(OBJECTS) $(OBJECTS_B)

clean : 
	rm -f $(OBJECTS) $(OBJECTS_B) $(OBJECTS_FT_PRINTF)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all re clean fclean
