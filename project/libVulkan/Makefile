#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:31:12 by banthony          #+#    #+#              #
#    Updated: 2018/04/23 15:17:24 by banthony         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= debug.so

DIRSRC		= ./

DIROBJ		= ./

SRC			+=	Graphics.cpp

OBJ			=	$(SRC:.cpp=.o)
OBJS		=	$(OBJ:%=$(DIROBJ)%)

CC			=	/usr/bin/clang++
RM			=	/bin/rm -f
ECHO		=	/bin/echo

CFLAGS		=	-Wall -Wextra -Werror

VULKAN_FLAGS = 

all		:		$(NAME)

$(NAME)	:		$(OBJ)
				$(CC) $(CFLAGS) $(VULKAN_FLAGS) -shared -o $(NAME) $(OBJS)
				@$(ECHO) '> Compiled'

clean	:
				@(cd $(DIROBJ) && $(RM) $(OBJ))
				@$(ECHO) '> Directory cleaned'

fclean	:		clean
				-@$(RM) $(NAME) #'-' en cas d'erreur ne pas stop le makefile ; '@' silence la premiere ligne d'output (instruction rm ...)
				@$(ECHO) '> Remove executable'

re		:		fclean all

%.o		:		$(DIRSRC)/%.cpp
				$(CC) $(CFLAGS) -o $(DIROBJ)/$@ -c $<
