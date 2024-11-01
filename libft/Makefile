# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 17:54:43 by hamrachi          #+#    #+#              #
#    Updated: 2024/11/01 01:08:19 by yojablao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

FLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strcmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCBONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstlast_bonus.c

OBJS = ${SRCS:%.c=%.o}

OBJBONUS = ${SRCBONUS:%.c=%.o}

all : ${NAME}

%.o : %.c libft.h
	${CC} ${FLAGS} -c $< -o $@

${NAME} : ${OBJS} bonus
	ar rc ${NAME} ${OBJS}
	
bonus : ${OBJBONUS}
	ar rc ${NAME} ${OBJBONUS}
	
clean :
	rm -f ${OBJS} ${OBJBONUS}

fclean : clean
	rm -f ${NAME}

re : fclean all