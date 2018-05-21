OBJECTS_NAME_FOLDER = objs

SOURCES_NAME_FOLDER = srcs

FILES =				main.cpp \
					AGraphics.cpp \
					Nibbler.cpp \
					SceneMenu.cpp \
					SceneGameEnd.cpp \
					SceneGame.cpp \
					SceneSkin.cpp \
					DeltaTime.cpp

SRCS =				$(addprefix $(SOURCES_NAME_FOLDER)/, $(FILES))

OBJS =				$(addprefix $(OBJECTS_NAME_FOLDER)/, $(FILES:.cpp=.o))

CC =				g++ -std=c++11

NAME =				nibbler

DEBUGSEGFAULT =		-g3 -fsanitize=address

FLAGS = $(DEBUGSEGFAULT)

FLAGS +=				-Wall -Wextra -Werror


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
	make clean -C libSDL
	make clean -C libSFML
	make clean -C libOpenGL

fclean: objs_rm
	$(RM) $(NAME)
	make fclean -C libSDL
	make fclean -C libSFML
	make fclean -C libOpenGL

re: fclean all

r: objs_rm
	$(RM) $(NAME)
	@make nibbler

lib: sdl sfml opengl

libre: sdlre sfmlre openglre

reset: fclean
	cd ./libSFML/SFML/ && git clean -d -f
	$(RM) ./incl/GLFW
	$(RM) ./incl/stb_image.h

sdl:
	-make -C libSDL

sdlre:
	make re -C libSDL

sfml:
	-make -C libSFML

sfmlre:
	make re -C libSFML

opengl:
	-make -C libOpenGL

openglre:
	make re -C libOpenGL


