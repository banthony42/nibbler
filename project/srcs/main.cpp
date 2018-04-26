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

void	dlerror_wrapper(void) {
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(0);
}

AGraphics   *load_library(char *arg, void **dl_handle) {
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

int		main(int argc, char **argv) {
	Nibbler *nibbler;
    void *dl_handle;

	if (argc != 2)
		return (0);
    nibbler = Nibbler::getInstance();
    Nibbler::aGraphics = load_library(argv[1], &dl_handle);
    if (Nibbler::aGraphics == NULL)
        dlerror_wrapper();

//	nibbler->_aGraphics->helloWorld();
    nibbler->run();


	dlclose(dl_handle);
	return (0);
}














