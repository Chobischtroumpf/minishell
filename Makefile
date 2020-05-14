
# ================================ VARIABLES ================================= #

NAME	= minishell
CXX	= gcc
CFLAGS	= -Wall -Werror -Wextra

SRCDIR	= srcs/
INCDIR	= include/
OBJDIR	= objs/

CXXFLAGS	+= -I $(INCDIR)

SRCS	= 	$(SRCDIR)cmd_add_rdir.c $(SRCDIR)cmd_parser_1.c				\
			$(SRCDIR)cmd_parser_2.c $(SRCDIR)errors.c $(SRCDIR)free.c		\
			$(SRCDIR)exec_builtin.c $(SRCDIR)get_static.c $(SRCDIR)lexing.c	\
			$(SRCDIR)minishell.c $(SRCDIR)utils.c

SRC		:= $(notdir $(SRCS)) # 					Files only
OBJ		:= $(SRC:.c=.o)	#					Files only
OBJS	:= $(addprefix $(OBJDIR), $(OBJ)) #		Full path
CSRCS	:= $(addprefix ../, $(SRCS)) #			Compiler

GR	= \033[32;1m #	Green
RE	= \033[31;1m #	Red
YE	= \033[33;1m #	Yellow
CY	= \033[36;1m #	Cyan
RC	= \033[0m #	Reset Colors

# ================================== RULES =================================== #

all : $(NAME)

#	linking
$(NAME)	: $(OBJS)
	@printf "$(YE)&&& Linking $(OBJ) to $(NAME)$(RC)"
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) -I./libft/includes/ libft.a

#	compiling
$(OBJS) : $(SRCS)
	@printf "$(GR)+++ Compiling $(SRC) to $(OBJ)$(RC)"
	@mkdir -p $(OBJDIR)
	@cp libft/libft.a .
	@cd $(OBJDIR) && $(CXX) $(CXXFLAGS) -I ../$(INCDIR) -c $(CSRCS) -I../libft/includes/

#	runnng

run : $(NAME)
	@echo "$(CY)>>> Running $(NAME)$(RC)"
	./$(NAME)
#	cleaning
clean :
	@echo "$(RE)--- Removing $(OBJ)$(RC)"
	@rm -fd $(OBJS) $(OBJDIR)

fclean : clean
	@echo "$(RE)--- Removing $(NAME)$(RC)"
	@rm -f $(NAME)

re : fclean all

debug :
	@echo "SRCS $(SRCS)"
	@echo "SRC $(SRC)"
	@echo "OBJS $(OBJS)"
	@echo "OBJ $(OBJ)"
	@echo "CSRCS $(CSRCS)"
	@echo "CFLAGS $(CFLAGS)"

.PHONY	= all run clean fclean re debug
