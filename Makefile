# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 12:37:50 by bhagenlo          #+#    #+#              #
#    Updated: 2022/10/18 16:15:53 by bhagenlo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf

SRC := main.c lip.c draw.c data.c map.c 3d.c
SOBS := $(SRC:.c=.o)

LIBFT := libft
LIBMLX := MLX42
LFT := libft/libft.a
LMLX := MLX42/libmlx42.a

CC := cc
CF := -Wall -Wextra -Werror
C_UNSAFE := -Wall
LS := $(LFT) $(LMLX) -I include -lglfw -L "/Users/bhagenlo/.brew/opt/glfw/lib/"

RM := rm -rf

all: $(NAME)

$(NAME): $(SRC)
	@make -C $(LIBFT)
	@make -C $(LIBMLX)
	$(CC) $(SRC) $(LS) -o $(NAME)

clean:
	@make -C $(LIBFT) clean
	@make -C $(LIBMLX) clean
	$(RM) $(SOBS)

fclean: clean
	@make -C $(LIBFT) fclean
	@make -C $(LIBMLX) fclean
	$(RM) $(NAME)

re: fclean
	make all

debug: CF += -g
debug: all

.PHONY: all clean fclean re debug
