SRCS_DIR = srcs

OBJS_DIR = objs

SRCS	:=	$(shell find srcs/*.c -exec basename \ {} \;)

OBJS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}

HEADERS = minishell.h

LIB = ./libft/libft.a

NAME = minishell

CC = gcc

# make && valgrind --suppressions=./suppres.txt ./minishell
# --suppressions=./suppres.txt
CFLAGS =
# CFLAGS = -Werror -Wall -Wextra

# -- RULES -- #

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADERS} ${LIB}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -L/usr/local/lib -I/usr/local/include -lreadline -o ${NAME}
	@echo "\033[32m$ ${NAME} compiled !"
	@echo "----------------------------\033[0m"

all: ${NAME}

${LIB}:
	@make -sC ./libft

$(OBJS_DIR):
	@mkdir -p ${OBJS_DIR}
	@echo "\033[33mCompiling Philo..."

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@rm -rf ${OBJS_DIR}
	@echo "\033[32mClean !\033[0m"

fclean: clean
	@make fclean -sC ./libft
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re
