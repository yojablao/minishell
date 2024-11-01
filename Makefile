NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

READLINE_L = ~/.brew/opt/readline/lib
READLINE_I = ~/.brew/opt/readline/include
LDFLAGS = -L $(READLINE_L) -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SOURCES = \
	main.c bulting/b_env.c bulting/cd.c bulting/echo.c bulting/exit.c \
	bulting/export1.c bulting/export2.c bulting/export3.c bulting/pwd.c \
	bulting/unset.c bulting/unset1.c \
	exec/env_tools.c exec/env_utils.c exec/exec.c exec/execution.c \
	exec/minishell.c exec/pipe_line.c exec/pipe_utils.c exec/tools.c exec/utils.c \
	expanding/expanding1.c expanding/expanding2.c expanding/expandingtools1.c expanding/expandingtools2.c \
	parsing/comond_init.c parsing/f_split.c parsing/herdoc.c parsing/heredoc_utils.c \
	parsing/init.c parsing/init2.c parsing/malloc.c parsing/malloc_utils.c \
	parsing/parsing.c parsing/parsing_utils.c parsing/redirect.c \
	parsing/syntax1.c parsing/syntax2.c parsing/syntax3.c parsing/syntax4.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I $(READLINE_I) -I $(LIBFT_DIR) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

push:
	git add .
	git commit -m "done"
	git push

.PHONY: all clean fclean re push