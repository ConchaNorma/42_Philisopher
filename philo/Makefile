# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 21:44:20 by cnorma            #+#    #+#              #
#    Updated: 2022/01/06 15:27:44 by cnorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo
SRC_DIR = ./src/

SRC_FILES =	main.c init.c support.c simulation.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/

OBJ = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

HEADER = philo.h

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

.PHONY: all re clean fclean

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ) $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
