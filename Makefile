# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmelinda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 15:26:22 by pmelinda          #+#    #+#              #
#    Updated: 2020/10/17 15:26:26 by pmelinda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libasm.a

SRCS	= ft_strlen.s \
		  ft_strcpy.s \
		  ft_strcmp.s \
		  ft_strdup.s \
		  ft_write.s \
		  ft_read.s \

OBJS	= $(SRCS:.s=.o)

%.o		: %.s
	nasm -f macho64 $<

all		: $(NAME)

$(NAME)	: $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean	: 
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME) $(TEST) $(TXT) $(NAME)

re		: fclean all

test1   : 
	gcc -Wall -Wextra -Werror main.c -L. libasm.a

test2	:
	gcc -Wall -Wextra -Werror main_additional.c -L. libasm.a

.PHONY: all clean fclean re test1 test2
