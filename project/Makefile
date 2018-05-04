# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/05 10:57:06 by cchameyr          #+#    #+#              #
#    Updated: 2018/05/04 09:37:15 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJECTS_NAME_FOLDER = objs

SOURCES_NAME_FOLDER = srcs

FILES =				main.cpp \
					Nibbler.cpp \
					SceneMenu.cpp \
					SceneGameEnd.cpp \
					SceneGame.cpp \
					SceneSkin.cpp

SRCS =				$(addprefix $(SOURCES_NAME_FOLDER)/, $(FILES))

OBJS =				$(addprefix $(OBJECTS_NAME_FOLDER)/, $(FILES:.cpp=.o))

CC =				g++ -std=c++11

NAME =				nibbler

DEBUGSEGFAULT =		-g3 -fsanitize=address

FLAGS =				-Wall -Wextra -Werror

FLAGS += #$(DEBUGSEGFAULT)

RM =				rm -rf

all: $(NAME) lib

$(NAME): $(OBJS) $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS):
	$(CC) $(FLAGS) -c $(SRCS)
	@make objs_mv

objs_mv:
	@mkdir $(OBJECTS_NAME_FOLDER)
	@mv $(FILES:.cpp=.o) $(OBJECTS_NAME_FOLDER)

objs_rm:
	@$(RM) $(OBJECTS_NAME_FOLDER)
	@$(RM) $(FILES:.cpp=.o)

clean: objs_rm
	make clean -C libVulkan
	make clean -C libSFML
	make clean -C libOpenGL

fclean: objs_rm
	$(RM) $(NAME)
	make fclean -C libVulkan
	make fclean -C libSFML
	make fclean -C libOpenGL

re: fclean all

r: objs_rm
	$(RM) $(NAME)
	@make

lib: vulkan sfml opengl

libre: vulkanre sfmlre openglre

reset: fclean
	cd ./libSFML/SFML/ && git clean -d -f
	rm -rf ./libVulkan/Vulkan

vulkan:
	-make -C libVulkan

vulkanre:
	make re -C libVulkan

sfml:
	-make -C libSFML

sfmlre:
	make re -C libSFML

opengl:
	-make -C libOpenGL

openglre:
	make re -C libOpenGL


