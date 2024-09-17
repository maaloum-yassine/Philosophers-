# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 15:59:50 by ymaaloum          #+#    #+#              #
#    Updated: 2024/09/17 05:55:14 by ymaaloum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC				=	cc
CCFLAGS			=	-Wall -Wextra -Werror
NAME			=	philo
NAME_BONUS		=	philo_bonus

SRC				=	./mandatory/main.c \
					./mandatory/philosophers_actions.c \
					./mandatory/philosophers_utils1.c \
					./mandatory/philosophers_utils2.c \
					./mandatory/philosophers_utils3.c \

SRC_BONUS		=	./bonus/main_bonus.c \
					./bonus/philosophers_actions_bonus.c \
					./bonus/philosophers_utl1_bonus.c \
					./bonus/philosophers_utl2_bonus.c \
					./bonus/philosophers_utl3_bonus.c \

RESET			=	\033[1;97m
GREEN			=	\033[1;32m
RED				=	\033[1;31m

OBJ_DIR			=	obj/
OBJ				=	$(patsubst ./mandatory/%.c,$(OBJ_DIR)%.o,$(SRC))
OBJ_BONUS		=	$(patsubst ./bonus/%.c,$(OBJ_DIR)%.o,$(SRC_BONUS))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@echo "$(GREEN)$(OBJ_DIR) : Created ! [^_^]$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) : Created ! [^_^]$(RESET)"

$(OBJ_DIR)%.o: ./mandatory/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

bonus: $(OBJ_DIR) $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	@$(CC) $(CCFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)
	@echo "$(GREEN)$(NAME_BONUS) : Created ! [^_^]$(RESET)"

$(OBJ_DIR)%.o: ./bonus/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(NAME) : obj directory deleted ! [^_^]$(RESET)"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(RED)$(NAME) and $(NAME_BONUS) : obj directory and executable files deleted ! [^_^]$(RESET)"

re: fclean all
