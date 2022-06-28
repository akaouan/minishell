# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 17:25:48 by ael-hayy          #+#    #+#              #
#    Updated: 2022/06/10 16:32:13 by ael-hayy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=		gcc
CFLAGS		=		-Wall -Wextra -Werror
INCLUDE		=		-I Headers
CLABRARY	=		-readline

NAME		=		minishell

SOURCE		=		being_ready.c free.c \
					m_shell_tree.c minishell.c \
					open_files.c pre_line_check.c \
					redirection.c set_env.c tree_parser.c

OBJDIR		=		objects

$(NAME): $(OBJDIR) $(SOURCE)
		$(CC) $(CFLAGS) $(OBJDIR)/*.o -o $(NAME)

$(SOURCE): $(OBJDIR)
		$(CC) $(CFLAGS) $(SOURCE) -c -o $(OBJDIR)

$(OBJDIR):
		mkdir -p $(OBJDIR)


