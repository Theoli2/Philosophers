# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 17:59:00 by tlivroze          #+#    #+#              #
#    Updated: 2023/09/26 23:24:05 by tlivroze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wextra -Wall -Werror -g3 #-fsanitize=thread -g3
NAME		= philosophers

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
			ft_atoi.c \
			ft_itoa.c \
			ft_strlen.c \
			ft_strncmp.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(OBJ_PATH) $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm: 
	norminette $(SRC_PATH)

.PHONY: all clean fclean re