# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:23:56 by yojablao          #+#    #+#              #
#    Updated: 2024/10/23 15:25:06 by yojablao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = $(shell find . -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS =   -Wall -Wextra -Werror  -g -fsanitize=address

READ = -lreadline
$(NAME) : $(OBJECTS) 
	$(CC) $(CFLAGS) $(READ) $(OBJECTS) -o $(NAME)

%.o : %.c fractol.h
	$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)


push:
	git add .
	git commit -m "yojablao"
	git push
re: fclean all