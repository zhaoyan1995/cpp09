# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 01:56:34 by yanzhao           #+#    #+#              #
#    Updated: 2026/06/27 22:42:32 by yanzhao          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./RPN

OBJS_PATH=./objs/

SRCS=main.cpp RPN.cpp

OBJS=$(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))

DEPS=$(addprefix $(OBJS_PATH), $(SRCS:.cpp=.d))

HEADER_PATH=./

CC=c++

CFLAGS= -Wall -Wextra -Werror -std=c++98

DEPFLAGS=-MMD -MP

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_PATH)%.o:%.cpp
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(HEADER_PATH) -c $< -o $@

clean:
	rm -rf $(OBJS_PATH)

fclean:clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

# ./RPN "7 7 * 7 -" (42)
# ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +" (42)
# ./RPN "1 2 + 3 4 + *" (21)
# ./RPN "1   2   +" (3)
# ./RPN "1 +" (Error)
# ./RPN "1 2 3 +" (Error)
# ./RPN "+" (Error)
# ./RPN "1 2 + +" (Error)
# ./RPN "9 0 /" (Error)
# ./RPN "5 3 %" (Error)
# ./RPN "12 3 +" (15)
# ./RPN "1 (2 +)" (Error)
# ./RPN "" (Error)
# ./RPN "     " (Error)
# ./RPN "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *" (387420489)
# ./RPN "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 1 *" (387420489)
# ./RPN "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 2 *" (774840978)
# ./RPN "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *" (Error)
# ./RPN "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * ! *" (Error)
#  