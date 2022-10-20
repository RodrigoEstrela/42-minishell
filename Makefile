# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 10:31:48 by rdas-nev          #+#    #+#              #
#    Updated: 2022/10/20 13:55:16 by rdas-nev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		main.c sighandler.c commandsmaster.c builtins.c ft_strncmp.c \
					listfuncs.c builtins_export_utils.c split.c \
					pipex/children.c pipex/ft_memcmp.c pipex/get_next_line.c \
					pipex/get_next_line_utils.c pipex/heredoc.c \
					pipex/pipex.c pipex/pipex_utils.c pipex/quote_splitter.c export.c \
					unset.c parser.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror #-L/usr/include/readline -lreadline
RM			=		rm -f

NAME		= 		minishell

objs/%.o: srcs/%.c
			@mkdir -p objs
			@mkdir -p objs/pipex
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME) -L/usr/include/readline -lreadline

all:      	$(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)  
re:         fclean all
