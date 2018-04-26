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

#include "../incl/nibbler.hpp"
#include "../incl/AGraphics.hpp"
#include <dlfcn.h>
#include <iostream>

void	dlerror_wrapper(void) {
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(0);
}

int     load_library() {
    
}

int		main(int argc, char **argv) {
	void	*dl_handle;
	AGraphics *(*createGraphics)();
	AGraphics *graphics;

	if (argc != 2)
		return (0);
	dl_handle = dlopen(argv[1], RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle)
		dlerror_wrapper();

	// get createGraphics function
	createGraphics = (AGraphics *(*)()) dlsym(dl_handle, "createGraphics");
	if (!createGraphics)
		dlerror_wrapper();

	// get Grapgics
	graphics = createGraphics();

	graphics->helloWorld();

	dlclose(dl_handle);
	return (0);
}

