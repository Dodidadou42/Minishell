NAME	= minishell

SRCS	= srcs/minishell.c srcs/parsing.c srcs/parsing_utils.c	\
		  srcs/metacharacter.c srcs/execution.c srcs/history1.c \
		  srcs/history2.c srcs/cd1.c srcs/cd2.c \
		  srcs/builtin1.c srcs/builtin2.c srcs/signal.c	\
		  srcs/utils1.c srcs/utils2.c srcs/errors.c



OBJS 	= 	${SRCS:.c=.o}

CC		= gcc

LIBFT	= -Lincludes/libft -lft

CFLAGS	= -Wall -Wextra -Werror

READLINE = -lreadline -L/Users/${USER}/.brew/opt/readline/lib -I/Users/${USER}/.brew/opt/readline/include

GREEN	= \033[32m

YELLOW	= \033[33m

WHITE	= \033[37m

RED		= \033[0;31m

all:	check_brew check_readline ${NAME}

.c.o:	
		@echo "${WHITE}Compiling object $<"
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		@tput cuu1 && tput dl1

${NAME}:	${OBJS}
			@echo "${GREEN}Objects OK"
			@echo "${WHITE}Compiling Libft..."
			@make -s -C includes/libft
			@tput cuu1 && tput dl1
			@echo "${GREEN}Libft OK"
			@echo "${WHITE}Compiling Minishell..."
			@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${READLINE} -o ${NAME}
			@tput cuu1 && tput dl1
			@echo "${GREEN}Minishell OK"

check_brew:
	@if test ! $$(which brew); then \
	    echo "${RED}Brew is not installed. ${WHITE}Installing now..."; \
	    /bin/bash -c "$$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"; \
	fi
	@echo "${GREEN}Brew OK"

check_readline:
	@if test -z "$$(brew list | grep readline)"; then \
	    echo "${RED}Readline is not installed. ${WHITE}Installing now..."; \
	    brew install readline; \
	fi
	@echo "${GREEN}Readline OK"

clean:
		@echo "${WHITE}Cleaning objects..."
		@rm -f ${OBJS}
		@tput cuu1 && tput dl1
		@echo "${YELLOW}Objects cleaned"
		@echo "${WHITE}Cleaning Libft..."
		@make -s -C includes/libft clean
		@rm -f includes/libft/libft.a
		@tput cuu1 && tput dl1
		@echo "${YELLOW}Libft cleaned"

fclean: clean
		@echo "${WHITE}Cleaning Minishell"
		@rm -f ${NAME}
		@tput cuu1 && tput dl1
		@echo "${YELLOW}Minishell Cleaned"

re: fclean all

.PHONY: all clean fclean re check_brew check_readline
