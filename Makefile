#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 17:44:48 by trmoreau          #+#    #+#              #
#    Updated: 2016/12/07 08:03:59 by trmoreau         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	fillit

HEADER		=	fillit.h

CC			=	gcc

CFLAG		=	-Wall -Wextra -Werror

OPTION		=	-o $(NAME) -I $(HEADER)

SRCS		=	main.c		\
				utility.c	\
				pars_it.c	\
				fillit.c	\
				util_fillit.c \
				tetri.c

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	@$(CC) -c $(CFLAG) $(SRCS)
	@$(CC) $(CFLAG) $(OPTION) $(OBJS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
