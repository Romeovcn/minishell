SRCS_DIR = srcs

OBJS_DIR = objs

SRCS	=	00_main.c \
			01_built_in.c \
			02_check_access.c \
			03_env.c \
			04_utils.c \
			05_lexer.c \
			06_lexer_lst_utils.c \
			07_lexer_utils.c \
			08_token.c \
			09_token_lst_utils.c \

OBJS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}

HEADERS = minishell.h

LIB = ./libft/libft.a

NAME = minishell

CC = gcc

# CFLAGS = -Werror -Wall -Wextra
CFLAGS = 

# -- RULES -- #

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADERS} ${LIB}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -L/usr/local/lib -I/usr/local/include -lreadline -o ${NAME}
	@echo "\033[32m$ ${NAME} compiled !"
	@echo "----------------------------\033[0m"

all: ${NAME}

${LIB}:
	@make -C ./libft

$(OBJS_DIR):
	@mkdir -p ${OBJS_DIR}
	@echo "\033[33mCompiling Philo..."

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@rm -rf ${OBJS_DIR}
	@echo "\033[32mClean !\033[0m"

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re