# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 15:59:50 by ymaaloum          #+#    #+#              #
#    Updated: 2023/05/29 19:08:53 by ymaaloum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo_bonus

SRC =	main_bonus.c\
		philosophers_utl1_bonus.c \
		philosophers_utl2_bonus.c \
		philosophers_actions_bonus.c \
		philosophers_utl3_bonus.c \

all: $(NAME)
$(NAME) : $(SRC)
		@$(CC) $(CFLAGS) $(SRC) -o $@
clean :
		@rm -f $(NAME)

fclean : clean

re : fclean all
