NAME	= minishell

SRCS	= srcs/minishell.c srcs/parsing.c srcs/parsing_utils.c	\
		  srcs/metacharacter1.c srcs/metacharacter2.c	\
		  srcs/builtin1.c srcs/builtin2.c srcs/builtin3.c srcs/execution.c	\
		  srcs/signal.c srcs/utils.c srcs/errors.c

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

LIBFT	= -Lincludes/libft -lft

READLINE = -lreadline

OBJS 	= ${SRCS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -s -C includes/libft
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${READLINE} -o ${NAME}

all:	${NAME}

clean:
		rm -f ${OBJS}
		make -s -C includes/libft clean

fclean: clean
		rm -f ${NAME} includes/libft/libft.a

re: fclean all

.PHONY: all clean fclean re
