# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    configure.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 18:10:22 by banthony          #+#    #+#              #
#    Updated: 2018/05/04 15:05:41 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vulkan_tar="./libVulkan/vulkanLib.tar.gz"
vulkan_src="./libVulkan/Vulkan"

image_loader="./incl/stb_image.h"
glfw_folder="./incl/GLFW"
glfw3="./incl/GLFW/glfw3.h"


# Pull des submodule
git submodule init
git submodule update

#Install OpenGL and Vulkan dependences
brew install pkg-config && brew install glfw && brew install glew && brew install glm && brew install glfw3

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
	mkdir glfw_folder
	curl https://raw.githubusercontent.com/glfw/glfw/master/include/GLFW/glfw3.h > $glfw3
fi



#Dl Vulkan sources if necessary
if [ -f "$vulkan_tar" ]
then
	echo "$vulkan_tar found."
else
	echo "$vulkan_tar, downloading ..."
	curl https://sdk.lunarg.com/sdk/download/1.0.69.0/mac/vulkansdk-macos-1.0.69.0.tar.gz > $vulkan_tar
fi

mkdir $vulkan_src
tar -xzf $vulkan_tar -C $vulkan_src --strip-components=1

# Compilation de la Lib
(cd ./LibSFML/SFML && cmake . && make -j4);
