# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpinheir <lpinheir@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 12:49:14 by lpinheir          #+#    #+#              #
#    Updated: 2022/02/17 11:40:26 by lpinheir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

INCLUDES = -I includes

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

RM_FLAGS = -f

S_DIR = srcs
O_DIR = objs

SRCS = $(S_DIR)/main.c \
	$(S_DIR)/utils.c \
	$(S_DIR)/string_utils.c \
	$(S_DIR)/ft_split.c \

OBJS = $(subst $(S_DIR), $(O_DIR), $(SRCS:.c=.o))

$(O_DIR)/%.o:	$(S_DIR)/%.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS)

clean:
	rm $(RM_FLAGS) $(OBJS)

fclean:	clean
	rm $(NAME)

re: fclean all