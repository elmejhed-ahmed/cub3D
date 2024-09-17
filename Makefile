# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 15:18:17 by ael-mejh          #+#    #+#              #
#    Updated: 2024/09/17 13:38:20 by ael-mejh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub
CC	= cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
SRC = ft_split.c cub3D.c get_next_line_utils.c get_next_line.c
OBJ = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
