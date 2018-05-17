#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:31:12 by banthony          #+#    #+#              #
#    Updated: 2018/05/17 13:51:57 by cchameyr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= libgraph.so

DIRSRC		= .

DIROBJ		= ./

SRC			+=	Graphics.cpp

OBJ			=	$(SRC:.cpp=.o)
OBJS		=	$(OBJ:%=$(DIROBJ)%)

CC			=	/usr/bin/clang++
RM			=	/bin/rm -f
ECHO		=	/bin/echo

SDK_PATH = ./SFML

LDFLAGS= -I $(SDK_PATH)/include -L $(SDK_PATH)/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

CFLAGSCPP11 = -std=c++11

CLFAGS =  -fPIC

CFLAGS		+= -Wall -Wextra -Werror

all		:		$(NAME)

$(NAME)	:		$(OBJ)
				$(CC) $(LDFLAGS) $(CFLAGS) $(CFLAGSCPP11) -shared -o $(NAME) $(OBJS) -headerpad_max_install_names
				install_name_tool -change @rpath/libsfml-graphics.2.4.dylib `pwd`/$(SDK_PATH)/lib/libsfml-graphics.2.4.dylib $(NAME)
				install_name_tool -change @rpath/libsfml-audio.2.4.dylib `pwd`/$(SDK_PATH)/lib/libsfml-audio.2.4.dylib $(NAME)
				install_name_tool -change @rpath/libsfml-window.2.4.dylib `pwd`/$(SDK_PATH)/lib/libsfml-window.2.4.dylib $(NAME)
				install_name_tool -change @rpath/libsfml-system.2.4.dylib `pwd`/$(SDK_PATH)/lib/libsfml-system.2.4.dylib $(NAME)
				@$(ECHO) '> Compiled'

clean	:
				-@$(RM) $(OBJ)
				@$(ECHO) '> Directory cleaned'

fclean	:		clean
				-@$(RM) $(NAME)
				@$(ECHO) '> Remove executable'

re		:		fclean all

%.o		:		$(DIRSRC)/%.cpp
				$(CC) $(LDFLAGS) $(CFLAGSCPP11) -c $<
