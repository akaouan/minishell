# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 17:25:48 by ael-hayy          #+#    #+#              #
#    Updated: 2022/07/01 15:54:00 by ael-hayy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -fsanitize=address -g
RM = rm -f
NAME = minishell
FILES = *c  ./executor/*c ./executor/Build_in/*c

OBJECTS = $(FILES:.c=.o)

%.o : %.c
	@cc -c -Wall -Wextra -Werror $<

all:  $(NAME)

$(NAME): $(OBJECTS)
	@cd libft && make
	@cd ..
	@$(CC) $(CFLAGS) $(OBJECTS) -lreadline -o $(NAME) libft/libft.a

clean:
	$(RM) *.o
	cd libft && make clean
	cd ../

fclean: clean
	@cd libft && make fclean
	@cd ../
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
