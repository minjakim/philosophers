# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 16:54:06 by minjakim          #+#    #+#              #
#    Updated: 2021/09/13 12:50:03 by minjakim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

SRC			=	main.c

ifeq ($(MAKECMDGOALS),bonus)
CPPFLAGS	+=	-D BONUS=1
NAME		=	philo_bonus
SRC			+=	philo_bonus/dining.c
SRC			+=	philo_bonus/philo.c
else
NAME		=	philo
SRC			+= 	philo/dining.c
SRC			+= 	philo/philo.c
endif

OBJ			=	$(SRC:%.c=%.o)

all			:	$(NAME)

%.o			: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(NAME)		:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

bonus		:

clean		:

fclean		:

re			:
