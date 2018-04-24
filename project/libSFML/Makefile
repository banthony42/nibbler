#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:31:12 by banthony          #+#    #+#              #
#    Updated: 2018/04/24 14:52:18 by cchameyr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= debug.so

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

CFLAGS		= -Wall -Wextra -Werror

all		:		$(NAME)

$(NAME)	:		$(OBJ)
				$(CC) $(LDFLAGS) $(CFLAGS) -shared -o $(NAME) $(OBJS)
				@$(ECHO) '> Compiled'

clean	:
				-@$(RM) $(OBJ)
				@$(ECHO) '> Directory cleaned'

fclean	:		clean
				-@$(RM) $(NAME) #'-' en cas d'erreur ne pas stop le makefile ; '@' silence la premiere ligne d'output (instruction rm ...)
				@$(ECHO) '> Remove executable'

re		:		fclean all

%.o		:		$(DIRSRC)/%.cpp
				$(CC) $(LDFLAGS) -c $<

r		:
				make re
				g++ main.cpp $(LDFLAGS) $(CFLAGS) $(NAME)
				install_name_tool -change @rpath/libsfml-graphics.2.4.dylib $(SDK_PATH)/lib/libsfml-graphics.2.4.dylib a.out
				install_name_tool -change @rpath/libsfml-audio.2.4.dylib $(SDK_PATH)/lib/libsfml-audio.2.4.dylib a.out
				install_name_tool -change @rpath/libsfml-window.2.4.dylib $(SDK_PATH)/lib/libsfml-window.2.4.dylib a.out
				install_name_tool -change @rpath/libsfml-system.2.4.dylib $(SDK_PATH)/lib/libsfml-system.2.4.dylib a.out

