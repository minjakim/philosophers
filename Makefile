# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 16:54:06 by minjakim          #+#    #+#              #
#    Updated: 2021/09/13 13:14:02 by minjakim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

SRC			=	src/main.c
OBJ_DIR		=	obj/

ifeq ($(MAKECMDGOALS),bonus)
	CPPFLAGS	+=	-D BONUS=1
	NAME		=	philo_bonus
	SRC			+=	src/philo_bonus/dining.c
	SRC			+=	src/philo_bonus/philo.c
else
	NAME		=	philo
	SRC			+= 	src/philo/dining.c
	SRC			+= 	src/philo/philo.c
endif

OBJ			=	$(SRC:%.c=%.o)

all			:	$(NAME)

%.o			: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(NAME)		:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

bonus		:	all

clean		:
				rm $(OBJ)

fclean		:

re			:

.PHONY		:
