#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:31:12 by banthony          #+#    #+#              #
#    Updated: 2018/05/17 13:53:45 by cchameyr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= libgraph.so

DIRSRC		= .

DIROBJ		= ./

SRC			+=	Graphics.cpp

OBJ			=	$(SRC:.cpp=.o)

CC			=	/usr/bin/clang++
RM			=	/bin/rm -f
ECHO		=	/bin/echo

SDK_PATH	= ~/.brew

LDFLAGS		= -I $(SDK_PATH)/include -lSDL2 -lSDL2_image -L $(SDK_PATH)/lib

CFLAGSCPP11	= -std=c++11

CFLAGS		=

#CFLAGS		+= -Wall -Wextra -Werror

all		:		$(NAME)

$(NAME)	:		$(OBJ)
				$(CC) $(LDFLAGS) $(CFLAGS) $(CFLAGSCPP11) -shared -o $(NAME) $(OBJ)
				@$(ECHO) '> Compiled'

clean	:
				-@$(RM) $(OBJ)
				@$(ECHO) '> Directory cleaned'

fclean	:		clean
				-@$(RM) $(NAME)
				@$(ECHO) '> Remove executable'

re		:		fclean all

%.o		:		$(DIRSRC)/%.cpp
				$(CC) $(LDFLAGS) $(CFLAGS) $(CFLAGSCPP11) -c $<
