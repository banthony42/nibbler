#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:31:12 by banthony          #+#    #+#              #
#    Updated: 2018/04/23 17:19:14 by banthony         ###   ########.fr        #
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

VULKAN_SDK_PATH = ./Vulkan/macOS/

LDFLAGS = -I $(VULKAN_SDK_PATH)/include -L $(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

CFLAGS		= -std=c++11 `pkg-config --static --cflags glfw3` `pkg-config --static --cflags glm` #-Wall -Wextra -Werror

all		:		$(NAME)

$(NAME)	:		$(OBJ)
				$(CC) $(LDFLAGS) $(CFLAGS) -shared -o $(NAME) $(OBJS)
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

r		:
				make re
				g++ main.cpp $(LDFLAGS) $(CFLAGS) $(NAME)
			   install_name_tool -change @rpath/libvulkan.1.dylib ./Vulkan/macOS/lib/libvulkan.1.dylib a.out
