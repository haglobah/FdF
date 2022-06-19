# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 12:37:50 by bhagenlo          #+#    #+#              #
#    Updated: 2022/06/19 12:48:30 by bhagenlo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf

CC := cc
CF := -Wall -Wextra -Werror
C_UNSAFE := -Wall

SRC := main.c 
SOBS := $(SRC:.c=.o)

RM := rm -rf

all: $(NAME)

$(NAME): 

clean:
	# clean libft
	$(RM) $(SOBS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
