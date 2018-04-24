# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    configure.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 18:10:22 by banthony          #+#    #+#              #
#    Updated: 2018/04/24 12:34:50 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vulkan_tar="./libVulkan/vulkanLib.tar.gz"
vulkan_src="./libVulkan/Vulkan"

# Pull des submodule
git submodule init
git submodule update

#Install OpenGL and Vulkan dependences
brew install pkg-config && brew install glfw && brew install glew && brew install glm && brew install glfw3

#Dl Vulkan sources if necessary
if [ -f "$vulkan_tar" ]
then
	echo "$vulkan_tar found."
else
	curl https://sdk.lunarg.com/sdk/download/1.0.69.0/mac/vulkansdk-macos-1.0.69.0.tar.gz > $vulkan_tar
fi

mkdir $vulkan_src
tar -xzf $vulkan_tar -C $vulkan_src --strip-components=1

# Compilation de la Lib
(cd ./LibSFML/SFML && cmake . && make -j4);
