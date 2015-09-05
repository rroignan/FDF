# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/02 15:37:49 by rroignan          #+#    #+#              #
#    Updated: 2015/09/05 18:43:45 by rroignan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = executable

CFLAGS = -c -Wall -Wextra -Werror

LDFLAGS = -lmlx -framework OpenGL -framework AppKit

SRC = fdf.c ../get_Next_line/get_next_line.c

OBJ = $(SRC:.c=.o)

CC = gcc

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -L ../minilibx_macos -lmlx -L ../libft -lft -I. -I../libft -I../get_Next_line $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -L ../minilibx_macos -lmlx -L ../libft -lft $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all
