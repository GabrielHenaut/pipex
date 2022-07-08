# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 14:03:47 by ghenaut-          #+#    #+#              #
#    Updated: 2022/07/07 22:20:14 by ghenaut-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY	= all bonus clean fclean re

NAME		= pipex
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3


LIBFT	= libft.a
IFT		= -Ilibft -Llibft -lft

SRCS	= 	pipex.c \
			child.c \
			error.c \
			handle_file.c \
			init_data.c

B_SRCS	=   pipex_bonus.c \
			child_bonus.c \
			error_bonus.c \
			handle_file_bonus.c \
			init_data_bonus.c

OBJSDIR	= ./obj
OBJS	= $(addprefix ${OBJSDIR}/, ${SRCS:%.c=%.o})
B_OBJS	= $(addprefix ${OBJSDIR}/, ${B_SRCS:%.c=%.o})

all: ${NAME}
	@make clean

bonus: ${NAME}_bonus
	@make clean

${NAME}: ${OBJSDIR} ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${IFT} -o $@

${NAME}_bonus: ${OBJSDIR} ${B_OBJS}
	@${CC} ${CFLAGS} ${B_OBJS} ${IFT} -o $@

${OBJSDIR}:
	@mkdir -p $@

${OBJS}: | ${LIBFT}
${B_OBJS}: | ${LIBFT}

${OBJSDIR}/%.o: src/%.c includes/pipex.h Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${OBJSDIR}/%.o: bonus/%.c includes/pipex_bonus.h Makefile
	@${CC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	@${MAKE} -C libft/

clean:
	@${MAKE} clean -C libft
	@rm -rf ${OBJSDIR}

fclean: clean
	@${MAKE} fclean -C libft
	@rm -rf ${NAME} ${NAME}_bonus

re: fclean all

