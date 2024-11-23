# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 12:57:07 by aboukezi          #+#    #+#              #
#    Updated: 2024/11/22 19:11:03 by aelaen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra 
# valgrind --tool=helgrind ./multi_thread_loop_mutex

SRC = main.c \
      input_check.c \
	  set_the_table.c \
	  actions.c \
	  check_if_end.c \
      utils.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

debug: FLAGS += -g
debug: all

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re