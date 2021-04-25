# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 09:34:48 by rtrant            #+#    #+#              #
#    Updated: 2021/01/14 20:15:13 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/main.c \
		srcs/time_utils/utils.c \
		srcs/atoi.c \
		srcs/prints.c \
		srcs/thread_prints.c \
		srcs/in_thread/funcs_in_thread.c \
		srcs/in_thread/eat_utils.c \
		srcs/init.c \
		srcs/clear.c

FLAGS = -Wall -Wextra -Werror

NAME = philo_two

all:
	gcc $(FLAGS) -Ihdrs -o $(NAME) $(SRCS) -lpthread

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRCS) hdrs/*.h

.PHONY: all clean fclean re