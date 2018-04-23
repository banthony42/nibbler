# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    configure.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 18:10:22 by banthony          #+#    #+#              #
#    Updated: 2018/04/20 19:07:45 by banthony         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Initialise le fichier local de configuration
git submodule init
# Pull des submodule
git submodule update

# Compilation de la Lib
(cd ./LibSFML/SFML && cmake . && make);