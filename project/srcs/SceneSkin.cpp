/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneSkin.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:49:05 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:49:05 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneSkin.hpp"
#include "../incl/Nibbler.hpp"

SceneSkin::SceneSkin() {

}

SceneSkin::SceneSkin(SceneSkin const &copy) {
    *this = copy;
}

SceneSkin::~SceneSkin() {

}

SceneSkin &SceneSkin::operator=(SceneSkin const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

SceneSkin::SceneSkin(AGraphics *aGraphics) {
    this->_aGraphics = aGraphics;
}

void SceneSkin::eventHandler(std::vector<eEvent> eventList) {
	for (size_t j = 0; j < eventList.size(); j++) {
		if (eventList.at(j) == ECHAP) {
			Nibbler::setCurrentScene(MENU);
		}
	}
}

void SceneSkin::drawScene() {
	this->_aGraphics->clear();
	this->_aGraphics->putTexture(0, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
	this->_aGraphics->display();
}

























