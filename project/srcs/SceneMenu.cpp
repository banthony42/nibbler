/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneMenu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:59 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:59 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneMenu.hpp"

SceneMenu::SceneMenu() {

}

SceneMenu::SceneMenu(SceneMenu const &copy) {
	*this = copy;
}

SceneMenu::~SceneMenu() {

}

SceneMenu::SceneMenu(AGraphics *aGraphics) {
	this->_aGraphics = aGraphics;
}

SceneMenu &SceneMenu::operator=(SceneMenu const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

void SceneMenu::eventHandler(std::vector<eEvent> eventList) {
	for (size_t j = 0; j < eventList.size(); j++) {
		if (eventList.at(j) == ECHAP) {
			Nibbler::_aGraphics->closeWindow();
		}
	}
}

void SceneMenu::drawScene() {
	this->_aGraphics->clear();
	this->_aGraphics->putTexture(MENU_BCKG, 0, 0, Nibbler::WINDOW_WIDTH, Nibbler::WINDOW_HEIGHT);
	this->_aGraphics->putStrScreen("< Game >", 300, 150, 2);
	this->_aGraphics->putStrScreen("Options", 300, 200, 2);
	this->_aGraphics->putStrScreen("Exit", 300, 250, 2);
	this->_aGraphics->display();
}




















