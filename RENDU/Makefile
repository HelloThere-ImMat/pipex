CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra

PF_DIR	= lib/
LIB_NAME	= ftprintf
CFLAGS_PF = -L $(PF_DIR) -l$(LIB_NAME)

SRCS	=	pipex.c \
			str_utils.c \
			str_utils2.c \
			utils.c \
			ft_split.c \
			access.c
SRCS_DIR	= srcs/
SRCS_PATH	= $(addprefix $(SRCS_DIR), $(SRCS))

B_SRCS =	b_pipex.c \
			b_str_utils.c \
			b_str_utils2.c \
			b_utils.c \
			b_ft_split.c \
			b_access.c \
			b_processes.c
B_SRCS_DIR	= bonus_srcs/
B_SRCS_PATH	= $(addprefix $(SRCS_B_DIR), $(SRCS))

NAME	=	pipex
B_NAME	=	pipex_bonus

DEPS	=	pipex.h \
			b_pipex.h
DEPS_DIR	= deps/
DEPS_PATH	= $(addprefix $(DEPS_DIR), $(DEPS))

OBJS		=	$(SRCS:.c=.o)
OBJS_DIR	=	objs/
OBJS_PATH	=	$(addprefix $(OBJS_DIR), $(OBJS))

B_OBJS		=	$(B_SRCS:.c=.o)
B_OBJS_DIR	=	bonus_objs/
B_OBJS_PATH	=	$(addprefix $(B_OBJS_DIR), $(B_OBJS))

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(DEPS_PATH) ./lib/libftprintf.a
		@mkdir -p $(OBJS_DIR)
		@${CC} $(CFLAGS) -c $< -o $@

$(B_OBJS_DIR)%.o: $(B_SRCS_DIR)%.c $(DEPS_PATH) ./lib/libftprintf.a
		@mkdir -p $(B_OBJS_DIR)
		@${CC} $(CFLAGS) -c $< -o $@

all:		$(NAME)

bonus:		$(B_NAME)

printf:
	@make -C $(PF_DIR) --no-print-directory

$(B_NAME): printf $(B_OBJS_PATH)
	@$(CC) $(CFLAGS) $(B_OBJS_PATH) $(CFLAGS_PF) -o $(B_NAME)

$(NAME): printf ${OBJS_PATH}
	@$(CC) $(CFLAGS) $(OBJS_PATH) $(CFLAGS_PF) -o $(NAME)

valgrind : ${OBJS_PATH}
	@$(CC) $(CFLAGS) $(OBJS_PATH) -o $(NAME).vgr -g

clean_printf:
	@make clean -C $(PF_DIR) --no-print-directory

fclean_printf:
	@make fclean -C $(PF_DIR) --no-print-directory

clean: clean_printf
	@rm -rf ${OBJS_DIR} $(B_OBJS_DIR)

fclean:	clean fclean_printf
	@rm -f ${NAME} $(NAME).vgr $(B_NAME)

re:			fclean all

.PHONY:	all valgrind clean fclean re