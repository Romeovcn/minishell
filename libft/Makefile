SRCSDIR	= srcs

OBJSDIR	= objs

SRCS	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
ft_strmatch.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c ft_putchar.c ft_putnbr_hexa.c \
ft_putnbr.c ft_putnbr_u.c ft_putstr.c ft_putnbr_adress.c \
ft_printf.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
ft_lstiter.c ft_lstmap.c \
get_next_line.c get_next_line_utils.c

OBJS	= ${patsubst %.c,${OBJSDIR}/%.o,${SRCS}}

HEADERS	= libft.h get_next_line.h ft_printf.h

NAME	= libft.a

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

${NAME}:	${OBJSDIR} ${OBJS} ${HEADERS} Makefile
	@ar rcs ${NAME} ${OBJS}
	@echo "\033[32mLibft compiled !"

all:	${NAME}

$(OBJSDIR):
	@echo "\033[33mCompiling Libft..."
	@mkdir ${OBJSDIR}

${OBJSDIR}/%.o: ${SRCSDIR}/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@rm -rf ${OBJS} $(OBJSDIR)

fclean:	clean
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re
