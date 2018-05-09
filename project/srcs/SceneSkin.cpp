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

SceneSkin::SceneSkin(AGraphics **aGraphics) {
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
	(*this->_aGraphics)->clear();

	(*this->_aGraphics)->putTexture(SKIN_FRAME, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
	(*this->_aGraphics)->putTexture(SNAKE_H_PCM, PERCENTAGE(55, Nibbler::getWindowWidth()), PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, PERCENTAGE(55, Nibbler::getWindowWidth()) - 48, PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, PERCENTAGE(55, Nibbler::getWindowWidth()) - 96, PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, PERCENTAGE(55, Nibbler::getWindowWidth()) - 144, PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_H_SMB, PERCENTAGE(55, Nibbler::getWindowWidth()), PERCENTAGE(45, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, PERCENTAGE(55, Nibbler::getWindowWidth()) - 48, PERCENTAGE(45, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, PERCENTAGE(55, Nibbler::getWindowWidth()) - 96, PERCENTAGE(45, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, PERCENTAGE(55, Nibbler::getWindowWidth()) - 144, PERCENTAGE(45, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_H_HK, PERCENTAGE(55, Nibbler::getWindowWidth()), PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_HK, PERCENTAGE(55, Nibbler::getWindowWidth()) - 48, PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_HK, PERCENTAGE(55, Nibbler::getWindowWidth()) - 96, PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_HK, PERCENTAGE(55, Nibbler::getWindowWidth()) - 144, PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);

	(*this->_aGraphics)->display();
}

























