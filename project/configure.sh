# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    configure.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 18:10:22 by banthony          #+#    #+#              #
#    Updated: 2018/05/07 16:40:06 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

image_loader="./incl/stb_image.h"
glfw_folder="./incl/GLFW"
glfw3="./incl/GLFW/glfw3.h"


# Pull des submodule
git submodule init
git submodule update

#Install OpenGL and Vulkan dependences
brew install pkg-config && brew install glfw && brew install glew && brew install glm && brew install glfw3 && brew install sdl2 && brew install sdl2_image

#Install stb_image.h, image loader
if [ -f "$image_loader" ]
then
	echo "$image_loader found."
else
	echo "$image_loader, downloading ..."
	curl https://raw.githubusercontent.com/nothings/stb/master/stb_image.h > $image_loader
fi

#Install last glfw3.h, image loader
if [ -f "$glfw3" ]
then
	echo "$glfw3 found."
else
	echo "$glfw3, downloading ..."
	mkdir $glfw_folder
	curl https://raw.githubusercontent.com/glfw/glfw/master/include/GLFW/glfw3.h > $glfw3
fi

# Compilation de la Lib
(cd ./LibSFML/SFML && cmake . && make -j4);
