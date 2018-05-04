#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:31:12 by banthony          #+#    #+#              #
#    Updated: 2018/05/04 15:02:07 by cchameyr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= libgraph.so

DIRSRC		= .

DIROBJ		= ./

SRC			+=	Graphics.cpp

OBJ			=	$(SRC:.cpp=.o)
OBJS		=	$(OBJ:%=$(DIROBJ)%)

CC			=	/usr/bin/clang++ -std=c++11 
RM			=	/bin/rm -f
ECHO		=	/bin/echo

SDK_PATH = ./Vulkan/macOS/

LDFLAGS =  -L $(SDK_PATH)lib `pkg-config --static --libs glfw3` `pkg-config --static --libs glm` -lvulkan

CFLAGS		= -I ../incl/ -I $(SDK_PATH)include `pkg-config --static --cflags glm` -fPIC

CFLAGS += #-Wall -Wextra -Werror


all		:		$(NAME)

$(NAME)	:		$(OBJ)
				$(CC) $(LDFLAGS) $(CFLAGS) -shared -o $(NAME) $(OBJS)
				install_name_tool -change @rpath/libvulkan.1.dylib `pwd`/Vulkan/MoltenVK/macOS/libMoltenVK.dylib $(NAME)
				@$(ECHO) '> Compiled'

clean	:
				@(cd $(DIROBJ) && $(RM) $(OBJ))
				@$(ECHO) '> Directory cleaned'

fclean	:		clean
				-@$(RM) $(NAME) #'-' en cas d'erreur ne pas stop le makefile ; '@' silence la premiere ligne d'output (instruction rm ...)
				@$(ECHO) '> Remove executable'

re		:		fclean all

%.o		:		$(DIRSRC)/%.cpp
				$(CC) $(LDFLAGS) $(CFLAGS) -c $<
