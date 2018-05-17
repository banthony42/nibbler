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
				Nibbler::loadLibrary(std::string(av[++i]));
			libraryLoaded = true;
		} else if (strcmp(av[i], "-size") == 0 && i + 2 < ac) {
			if (is_digits(av[i + 1]) && is_digits(av[i + 2])) {
				t_coordi window = {};

				if (((window.x = std::stoi(av[++i])) < WINDOW_MIN_X) ||
					((window.y = std::stoi(av[++i])) < WINDOW_MIN_Y)) {
					throw std::runtime_error(std::string("The window size can't be inferior than ")
											 + std::to_string(WINDOW_MIN_X) + " x " + std::to_string(WINDOW_MIN_Y));
				}
				Nibbler::setWindowWidth(window.x);
				Nibbler::setWindowHeight(window.y);
			}
		} else {
			throw std::runtime_error("Arguments error");
		}
	}
	if (!libraryLoaded) {
			Nibbler::loadLibrary(std::string(LIB_OPENGL_PATH));
	}
}

int main(int argc, char **argv) {
	Nibbler *nibbler;

	std::srand(std::time(0));
	nibbler = Nibbler::getInstance();
	try {
		manageArguments(argc, argv);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		showHelp();
		exit(-1);
	}
	if (Nibbler::_aGraphics != nullptr) {
		try {
			nibbler->run();
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
		nibbler->closeDlHandle();
	}
	return (0);
}