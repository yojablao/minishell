NAME = minishell
SOURCES = $(shell find . -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror   #-fsanitize=address -g 

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
	git commit -m ""
re: fclean all
