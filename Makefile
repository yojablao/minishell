# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:23:56 by yojablao          #+#    #+#              #
#    Updated: 2024/10/31 15:36:20 by yojablao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = $(shell find . -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS =   -Wall -Wextra -Werror  -g #-fsanitize=address



READLINE_L = ~/.brew/opt/readline/lib
READLINE_I = ~/.brew/opt/readline/include

LDFLAG = -L $(READLINE_L) -lreadline

$(NAME) : $(OBJECTS) 
	$(CC) $(CFLAGS) $(LDFLAG) $(OBJECTS) -o $(NAME)

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c -I $(READLINE_I)  $< -o $@ 
all: $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)


push:
	git add .
	git commit -m "last_v"
	git push
re: fclean all