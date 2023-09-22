# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 17:59:00 by tlivroze          #+#    #+#              #
#    Updated: 2023/09/22 20:11:57 by tlivroze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
CFLAGS		= -Wextra -Wall -Werror -fsanitize=thread #-g3
NAME		= philosophers
BONUS_NAME	= checker

LIBFT_PATH	= ./libft/
LIBFT		= $(LIBFT_PATH)libft.a

SRC_PATH 	= srcs/
OBJ_PATH 	= obj/

SRC     =   main.c \
			init.c \
			free.c \
			routine.c \
			utils.c \
			monitoring.c \
			eat.c \
			atoi_bool.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/

 all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

norm: 
	norminette $(LIBFT_PATH) $(SRC_PATH)

.PHONY: all clean fclean re