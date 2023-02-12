# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 17:32:29 by mdorr             #+#    #+#              #
#    Updated: 2023/02/12 12:01:05 by mdorr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_printf.c ft_print_nbr.c ft_print_str.c


NAME	=	libftprintf.a


OBJS	= 	${SRCS:.c=.o}


HEADERS = includes/


CC	= 	gcc


CFLAGS	= 	-Wall -Wextra -Werror -I


.c.o:

		@${CC} ${CFLAGS} ${HEADERS} -c $< -o ${<:.c=.o}


${NAME}:	${OBJS}
		@ar rc ${NAME} ${OBJS}


all:	${NAME}


clean:
		@rm -f ${OBJS}


fclean:	clean
		@rm -f ${NAME}


re:	fclean all


.PHONY : 	all clean fclean re
