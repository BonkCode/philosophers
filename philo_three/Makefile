# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 09:34:48 by rtrant            #+#    #+#              #
#    Updated: 2021/04/25 14:56:52 by rtrant           ###   ########.fr        #
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
		srcs/clear.c \
		srcs/in_thread/init_thread_sems.c \
		srcs/create_philos_utils.c

FLAGS = -Wall -Wextra -Werror

NAME = philo_three

all:
	gcc $(FLAGS) -Ihdrs -o $(NAME) $(SRCS) -lpthread

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

norme:
	norminette $(SRCS) hdrs/*.h

.PHONY: all clean fclean re