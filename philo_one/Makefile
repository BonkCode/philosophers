# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 09:34:48 by rtrant            #+#    #+#              #
#    Updated: 2021/01/11 11:46:52 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/main.c \
		srcs/time_utils/utils.c \
		srcs/atoi.c \
		srcs/prints.c \
		srcs/thread_prints.c

FLAGS =

NAME = philo_one

all:
	gcc $(FLAGS) -Ihdrs -o $(NAME) $(SRCS) -lpthread

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re