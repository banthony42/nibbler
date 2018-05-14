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
	this->_cursor = SKIN_1;
}

void SceneSkin::eventHandler(std::vector<eEvent> eventList) {
	for (auto &event : eventList) {
		if (event == ECHAP) {
			Nibbler::setCurrentScene(MENU);
		}
		else if (event == ENTER) {
			Nibbler::setCurrentScene(GAME);
		}
	}
}

void SceneSkin::drawScene() {
	(*this->_aGraphics)->clear();

	(*this->_aGraphics)->putTexture(SKIN_FRAME, FRAME_START_X, FRAME_START_Y, FRAME_WIDTH, FRAME_HEIGHT);



    (*this->_aGraphics)->putTexture(SNAKE_H_SMB, PERCENTAGE(50, Nibbler::getWindowWidth()),
                                    PERCENTAGE(47, Nibbler::getWindowHeight()) - (SECTOR_DEFAULT_SIZE / 2), SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE);




    /*
	(*this->_aGraphics)->putTexture(SNAKE_H_PCM, PERCENTAGE(58, Nibbler::getWindowWidth()), PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, PERCENTAGE(58, Nibbler::getWindowWidth()) - 48, PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, PERCENTAGE(58, Nibbler::getWindowWidth()) - 96, PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, PERCENTAGE(58, Nibbler::getWindowWidth()) - 144, PERCENTAGE(11, Nibbler::getWindowHeight()), 48, 48);




	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, PERCENTAGE(50, Nibbler::getWindowWidth()) - 48, PERCENTAGE(50, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, PERCENTAGE(50, Nibbler::getWindowWidth()) - 96, PERCENTAGE(50, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, PERCENTAGE(50, Nibbler::getWindowWidth()) - 144, PERCENTAGE(50, Nibbler::getWindowHeight()), 48, 48);


	(*this->_aGraphics)->putTexture(SNAKE_H_HK, PERCENTAGE(58, Nibbler::getWindowWidth()), PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_HK, PERCENTAGE(58, Nibbler::getWindowWidth()) - 48, PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_HK, PERCENTAGE(58, Nibbler::getWindowWidth()) - 96, PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_HK, PERCENTAGE(58, Nibbler::getWindowWidth()) - 144, PERCENTAGE(80, Nibbler::getWindowHeight()), 48, 48);
*/
	(*this->_aGraphics)->display();
}

























