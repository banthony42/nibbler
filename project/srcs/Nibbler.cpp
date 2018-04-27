/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:51:20 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:51:20 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/nibbler.hpp"

Nibbler *Nibbler::_singleton = nullptr;
AGraphics *Nibbler::aGraphics = nullptr;

Nibbler::Nibbler() {

}

Nibbler::Nibbler(Nibbler const &copy) {
    *this = copy;
}

Nibbler::~Nibbler() {

}

Nibbler &Nibbler::operator=(Nibbler const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

Nibbler *Nibbler::getInstance() {
    if (!Nibbler::_singleton)
        Nibbler::_singleton = new Nibbler();
    return Nibbler::_singleton;
}

void Nibbler::run() {
    Nibbler::aGraphics->init();
	std::string key[NB_EVENT] = {"VOID", "ECHAP", "UP", "DOWN", "LEFT", "RIGHT", "ENTER",}; // debug

    while (Nibbler::aGraphics->loopUpdate()) {

		auto vec = Nibbler::aGraphics->getEvent();

//        _eventHandler[_state]();
//        _displayer[_state]();




        for (size_t j = 0; j < vec.size(); ++j) {

				std::cout << vec.size() << std::endl;
				std::cout << key[vec.at(j)] << std::endl;
		}



        // update
        // event
        // update nibbler
    }
    Nibbler::aGraphics->cleanUp();
}