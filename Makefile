CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra

PF_DIR	= lib/
LIB_NAME	= ftprintf
CFLAGS_PF = -L $(PF_DIR) -l$(LIB_NAME)

SRCS	=	pipex.c \
			str_utils.c \
			str_utils2.c \
			utils.c \
			utils2.c \
			arg_utils.c \
			ft_split.c \
			ft_split2.c \
			access.c \
			processes.c \
			read_input.c
SRCS_DIR	= srcs/
SRCS_PATH	= $(addprefix $(SRCS_DIR), $(SRCS))

B_SRCS =	pipex_bonus.c \
			str_utils_bonus.c \
			str_utils2_bonus.c \
			utils_bonus.c \
			utils2_bonus.c \
			utils3_bonus.c \
			arg_utils_bonus.c \
			ft_split_bonus.c \
			ft_split2_bonus.c \
			access_bonus.c \
			processes_bonus.c \
			here_doc_bonus.c \
			read_input_bonus.c
B_SRCS_DIR	= srcs_bonus/
B_SRCS_PATH	= $(addprefix $(SRCS_B_DIR), $(B_SRCS))

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

LIBFTPRINTF = ./lib/libftprintf.a
MAKEFILE	= Makefile

all:		$(NAME)

bonus:		$(B_NAME)

$(LIBFTPRINTF):
	@$(MAKE) -C $(PF_DIR) --no-print-directory

$(B_NAME): $(MAKEFILE) $(LIBFTPRINTF) $(B_OBJS_PATH) $(DEPS_PATH)
	@$(CC) $(CFLAGS) $(B_OBJS_PATH) $(CFLAGS_PF) -o $(B_NAME) -g

$(NAME): $(MAKEFILE) $(LIBFTPRINTF) $(OBJS_PATH) $(DEPS_PATH)
	@$(CC) $(CFLAGS) $(OBJS_PATH) $(CFLAGS_PF) -o $(NAME)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(DEPS_PATH)
		@mkdir -p $(OBJS_DIR)
		${CC} $(CFLAGS) -c $< -o $@

$(B_OBJS_DIR)%.o: $(B_SRCS_DIR)%.c $(DEPS_PATH)
		@mkdir -p $(B_OBJS_DIR)
		${CC} $(CFLAGS) -c $< -o $@

clean_printf:
	@$(MAKE) clean -C $(PF_DIR) --no-print-directory

fclean_printf:
	@$(MAKE) fclean -C $(PF_DIR) --no-print-directory

clean: clean_printf
	@$(RM) -rf ${OBJS_DIR} $(B_OBJS_DIR)

fclean:	clean fclean_printf
	@$(RM) -f ${NAME} $(NAME).vgr $(B_NAME)

re:			fclean all

.PHONY:	all bonus valgrind clean fclean re
