# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trofidal <trofidal@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 03:44:57 by trofidal          #+#    #+#              #
#    Updated: 2022/01/05 03:16:55 by trofidal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ircserv

CC=clang++ -Wall -Wextra -Werror -std=c++98 

RM=rm -rf

SRC= ./srcs/Data.cpp \
	./srcs/User.cpp	\
	./srcs/Server.cpp \
	./srcs/Command.cpp \
	./srcs/Channel.cpp \
	./srcs/Utils.cpp \
	./srcs/main.cpp		

OBJ=$(SRC:.cpp=.o)

$(NAME): $(OBJ)
	@printf $(blue)
	@$(CC) $(OBJ) -o $(NAME)
	@printf "\e[KCompilation done ./$(NAME) is ready to use\n"
	@printf $(reset_char)


%.o : %.cpp
	@printf $(blue)
	@printf "Generating $< object file\e[K\r"
	@$(CC) $(CDEF)  -o $@ -c $?

all: clean $(NAME)

clean:
	@printf $(green)
	@$(RM) $(OBJ)
	@printf "Cleared object files\n"
	@printf $(reset_char)
	
fclean: clean
	@printf $(green)
	@$(RM) $(NAME) $(NAME2)
	@printf "Cleared executable files\e[K\n"
	@printf $(reset_char)

noflags: clean
	$(CC) $(SRC) -o $(NAME)

re: fclean all

####	C	O	L	O	R	S	####
black 				=	"\e[1;30m"
red 				=	"\e[1;31m"
green 				=	"\e[1;32m"
yellow 				=	"\e[1;33m"
blue 				=	"\e[1;34m"
magenta 			=	"\e[1;35m"
cyan 				=	"\e[1;36m"
white 				=	"\e[1;37m"

bg_black 			=	"\e[40m"
bg_red 				=	"\e[41m"
bg_green 			=	"\e[42m"
bg_yellow 			=	"\e[43m"
bg_blue 			=	"\e[44m"
bg_magenta 			=	"\e[45m"
bg_cyan 			=	"\e[46m"
bg_white 			=	"\e[47m"

reset_char 				=	"\e[0m"
####	C	O	L	O	R	S	####
