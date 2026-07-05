# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 01:56:34 by yanzhao           #+#    #+#              #
#    Updated: 2026/06/25 22:41:50 by yanzhao          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./btc

OBJS_PATH=./objs/

SRCS=main.cpp BitcoinExchange.cpp

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