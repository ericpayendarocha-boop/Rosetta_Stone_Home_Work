# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/18 09:07:34 by ericpayen         #+#    #+#              #
#    Updated: 2026/10/18 15:36:30 by ericpayen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rush-02
DEBUG_NAME = debug.out
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -Wall -Wextra -Werror -g3

HEADER = rosetta.h

SRC = main.c load_dictionary.c dict_utils.c lookup_exception.c \
      print_dict_word.c print_triplet_value.c print_large_number.c check_input.c
OBJ = $(SRC:.c=.o)
DEBUG_OBJ = $(SRC:.c=_debug.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

debug: $(DEBUG_NAME)

$(DEBUG_NAME): $(DEBUG_OBJ)
	$(CC) $(DEBUG_FLAGS) $(DEBUG_OBJ) -o $(DEBUG_NAME)

%_debug.o: %.c $(HEADER)
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEBUG_OBJ)

fclean: clean
	rm -f $(NAME) $(DEBUG_NAME)

re: fclean all

.PHONY: all clean fclean re debug
