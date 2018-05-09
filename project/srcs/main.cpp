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

static void dlerror_wrapper(void) {
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(0);
}

static AGraphics *load_library(char *arg, void **dl_handle) {
	AGraphics *(*createGraphics)();

	*dl_handle = dlopen(arg, RTLD_LAZY | RTLD_LOCAL);
	if (!*dl_handle)
		dlerror_wrapper();

	// get createGraphics function
	createGraphics = (AGraphics *(*)()) dlsym(*dl_handle, "createGraphics");
	if (!createGraphics)
		dlerror_wrapper();

	// get Graphics
	return createGraphics();
}

int main(int argc, char **argv) {
	Nibbler *nibbler;
	void *dl_handle;

	nibbler = Nibbler::getInstance();
	dl_handle = nullptr;
	if (argc == 3) {
		if (is_digits(argv[1]) && is_digits(argv[2])) {
			Nibbler::setWindowWidth(std::stoi(argv[1]));
			Nibbler::setWindowHeight(std::stoi(argv[2]));
			Nibbler::_aGraphics = load_library(Nibbler::pathLibOpenGL, &dl_handle);
		}
	} else if (argc == 2) {
		Nibbler::_aGraphics = load_library(argv[1], &dl_handle);
	} else {
		Nibbler::_aGraphics = load_library(Nibbler::pathLibOpenGL, &dl_handle);
	}
	if (Nibbler::_aGraphics == NULL)
		dlerror_wrapper();
	if (dl_handle) {
		nibbler->
				run();
		dlclose(dl_handle);
	}
	return (0);
}





