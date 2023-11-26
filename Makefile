SRCS	=	main.c \
			utils_01.c \
			utils_02.c \
			utils_free.c \
			utils_init.c \
			les_sims_5.c \
			verif_dead.c

OBJS	=	$(SRCS:.c=.o)

CC	=	gcc -D_REENTRANT -pthread

CFLAGS	=	-Wall -Wextra -Werror

RM = rm -f

NAME	=	philo


all:	$(NAME)


.c.o:
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
		@echo "$(NOC)Compilation de $(NAME) $(NOC)"
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		@echo "$(RED)Destruction des .o$(NOC)"
		@$(RM) $(OBJS)

fclean:	clean
		@echo "$(RED)Destruction des .a$(NOC)"
		@$(RM) $(NAME)

re:		fclean all

norme:
	@echo "$(NOC)\n\tNorminette\n$(NOC)"
	@$(eval NORME_OUTPUT := $(shell norminette | grep -v "OK"))
	@if [ -z "$(NORME_OUTPUT)" ]; then \
		echo "$(GREEN)Les fichiers sont à la norme$(NOC)"; \
	else \
		echo "$(YELLOW)Il y a des erreurs de norme$(NOC)"; \
		echo "$(NORME_OUTPUT)\n"; \
	fi

val1:
	@echo "$(NOC)valgrind --tool=drd ./$(NAME)$(NOC)"

val2:
	@echo "$(NOC)valgrind --tool=helgrind ./$(NAME)$(NOC)"

### COLORS ###

NOC			= \033[0m
BOLD		= \033[1m
UNDERLINE	= \033[4m
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
