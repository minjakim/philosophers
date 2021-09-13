# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 16:54:06 by minjakim          #+#    #+#              #
#    Updated: 2021/09/13 14:33:26 by minjakim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra

SRC_DIR			=	./src
OBJ_DIR			=	./obj
RM				=	rm

SRC				=	main.c

ifeq ($(MAKECMDGOALS),bonus)
	CPPFLAGS	+=	-D BONUS=1
	NAME		=	philo_bonus
else
	NAME		=	philo
endif

SRC				+=	$(NAME)/dining.c
SRC				+=	$(NAME)/philo.c

SRCS			=	$(addprefix src/,$(SRC))
OBJS			=	$(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all				:	$(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p $(dir $(OBJ_DIR)/$*)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(NAME)			:	$(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) -o $(NAME)

bonus			:	all

clean			:
					$(RM) -rf $(OBJ_DIR)

fclean			:	clean
	@$(RM) $(NAME)

re				:	fclean	all

.PHONY			:	all bonus clean fclean re
