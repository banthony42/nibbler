/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:51:29 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:51:29 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_NIBBLER_HPP
#define PROJECT_NIBBLER_HPP

#include <iostream>
#include <dlfcn.h>
#include "AGraphics.hpp"

class Nibbler {

public:
    static AGraphics *aGraphics;

    static Nibbler *getInstance();
    void run();

private:
    static Nibbler *_singleton;

    Nibbler(); // Canonical
    Nibbler(Nibbler const &copy); // Canonical
    ~Nibbler(); // Canonical
    Nibbler &operator=(Nibbler const &copy); // Canonical
};


#endif //PROJECT_NIBBLER_HPP