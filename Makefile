OBJ_DIR = obj

SRCS	=	ft_split.c \
			pipex.c \
			utils.c \
			str_utils.c


NAME	=	./pipex

OBJS	= 	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC	= 	gcc

CFLAGS	= 	-Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	${CC} -c $< -o $@
#        |${CFLAGS}
#	  REMOVED THE FLAGS
clean:
	rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME} ${BONUS_NAME}

re: fclean all

.PHONY: all clean fclean re
