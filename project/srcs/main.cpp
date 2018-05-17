/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:08:52 by cchameyr          #+#    #+#             */
/*   Updated: 2018/04/26 10:39:14 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Nibbler.hpp"

static bool is_digits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

void showHelp() {
	std::cout << "help : ./nibbler [-size Width Height] [-lib pathLib]" << std::endl;
}

void manageArguments(int ac, char **av) {
	int i = 0;
	bool libraryLoaded = false;

	while (++i < ac) {
		if (strcmp(av[i], "-help") == 0) {
			showHelp();
			exit(0);
		}
		if (strcmp(av[i], "-lib") == 0 && i + 1 < ac) {
			if (!Nibbler::loadLibrary(std::string(av[++i]))) {
				showHelp();
				exit(0);
			}
			libraryLoaded = true;
		} else if (strcmp(av[i], "-size") == 0 && i + 2 < ac) {
			if (is_digits(av[i + 1]) && is_digits(av[i + 2])) {
                t_coordi window = {};
                if (((window.x = std::stoi(av[++i])) < WINDOW_MIN_X) || ((window.y = std::stoi(av[++i])) < WINDOW_MIN_Y)) {
                    std::cout << "The window size can't be inferior than " << WINDOW_MIN_X << " x " << WINDOW_MIN_Y << std::endl;
                    exit(0);
                }
				Nibbler::setWindowWidth(window.x);
				Nibbler::setWindowHeight(window.y);
			}
		} else {
			showHelp();
			exit(0);
		}
	}
	if (!libraryLoaded) {
		if (!Nibbler::loadLibrary(std::string(LIB_OPENGL_PATH))) {
			exit(0);
		}
	}
}

int main(int argc, char **argv) {
	Nibbler *nibbler;

	std::srand(std::time(0));
	nibbler = Nibbler::getInstance();
	manageArguments(argc, argv);
	if (Nibbler::_aGraphics != nullptr) {
		nibbler->run();
		nibbler->closeDlHandle();
	}
	return (0);
}





