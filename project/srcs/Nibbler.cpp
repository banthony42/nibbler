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

#include "../incl/Nibbler.hpp"

Nibbler *Nibbler::_singleton = nullptr;
AGraphics *Nibbler::_aGraphics = nullptr;

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

void Nibbler::initRun() {
    Nibbler::_aGraphics->init(Nibbler::WINDOW_WIDTH, Nibbler::WINDOW_HEIGHT);
    this->_callScene[MENU] = new SceneMenu(this->_aGraphics);
    this->_callScene[SKIN] = new SceneSkin(this->_aGraphics);
    this->_callScene[GAME] = new SceneGame(this->_aGraphics);
    this->_callScene[GAME_END] = new SceneGameEnd(this->_aGraphics);
    this->_currentScene = MENU;
}

void Nibbler::run() {
    this->initRun();
	std::string key[NB_EVENT] = {"VOID", "ECHAP", "UP", "DOWN", "LEFT", "RIGHT", "ENTER",}; // debug

    while (Nibbler::_aGraphics->loopUpdate()) {
		auto vec = Nibbler::_aGraphics->getEvent();

        this->_callScene[this->_currentScene]->eventHandler(vec);
        this->_callScene[this->_currentScene]->drawScene();

//        Nibbler::_aGraphics->closeWindow();

        // ************************************** DEBUG
        for (size_t j = 0; j < vec.size(); ++j) {

			std::cout << "size:" << vec.size() << std::endl;
			std::cout << key[vec.at(j)] << std::endl;

			if (vec.at(j) == ECHAP) {
				Nibbler::_aGraphics->closeWindow();
			}
		}
        // *************************************** DEBUG

        // update
        // event
        // update nibbler
    }
    Nibbler::_aGraphics->cleanUp();
}

