# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    configure.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 18:10:22 by banthony          #+#    #+#              #
#    Updated: 2018/05/18 14:42:56 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

image_loader="./incl/stb_image.h"

# Pull des submodule
git submodule init
git submodule update

#Install dependencies
brew install cmake
brew install pkg-config
brew install glfw
brew install glew
brew install glm
brew install glfw3
brew install sdl2
brew install sdl2_image

#Install stb_image.h, image loader
if [ -f "$image_loader" ]
then
	echo "$image_loader found."
else
	echo "$image_loader, downloading ..."
	curl https://raw.githubusercontent.com/nothings/stb/dev/stb_image.h > $image_loader
	error=${?}
	if [ !error ]
	then
		echo "Something goes wrong with the stb_image.h link, please visit this repo to get the file: https://github.com/nothings/stb"
	fi
fi

# Compilation de la Lib
(cd ./LibSFML/SFML && cmake . && make -j4);
