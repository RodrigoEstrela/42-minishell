# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 10:31:48 by rdas-nev          #+#    #+#              #
#    Updated: 2022/07/27 18:59:10 by rdas-nev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		main.c sighandler.c commandsmaster.c builtins.c ft_strncmp.c \
					listfuncs.c builtins_export_utils.c split.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-Wall -Wextra -Werror -lreadline -g 
RM			=		rm -f

NAME		= 		minishell

objs/%.o: srcs/%.c
			@mkdir -p objs
			@cc $(CFLAGS) -c $< -o $@

objs_bonus/%.o: bonus/%.c
			@mkdir -p objs_bonus
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME)

all:      	$(NAME)

bonus:		$(OBJS_BONUS)
			@cc $(OBJS_BONUS) $(CFLAGS) -o $(NAME)

clean:
			@$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			@$(RM) $(NAME)  
re:         fclean all