# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 01:56:34 by yanzhao           #+#    #+#              #
#    Updated: 2026/07/06 18:30:41 by yanzhao          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./PmergeMe

OBJS_PATH=./objs/

SRCS=main.cpp PmergeMe.cpp

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
		rm -f $(NAME) test1.txt test2.txt

re: fclean all

test1:
		./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "` > test1.txt
		@(awk -F':' 'NR==1 {print $$2}' test1.txt | tr ' ' '\n' | grep -v '^$$' | sort -n) > before1.txt
		@(awk -F':' 'NR==2 {print $$2}' test1.txt | tr ' ' '\n' | grep -v '^$$') > after1.txt
		@(diff before1.txt after1.txt && echo -e "\033[1;32m [SUCCESS] \033[0m") || (echo -e "\033[1;31m [FAILED] \033[0m" && diff before1.txt after1.txt)
		@rm before1.txt after1.txt 

test2:
		./PmergeMe `shuf -i 1-100000 -n 6000 | tr "\n" " "` > test2.txt
		@(awk -F':' 'NR==1 {print $$2}' test2.txt | tr ' ' '\n' | grep -v '^$$' | sort -n) > before2.txt
		@(awk -F':' 'NR==2 {print $$2}' test2.txt | tr ' ' '\n' | grep -v '^$$') > after2.txt
		@(diff before2.txt after2.txt && echo -e "\033[1;32m [SUCCESS] \033[0m") || (echo -e "\033[1;31m [FAILED] \033[0m" && diff before2.txt after2.txt)
		@rm before2.txt after2.txt

-include $(DEPS)

.PHONY: all clean fclean re test1 test2