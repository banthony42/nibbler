/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneGame.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:47 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:47 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneGame.hpp"

SceneGame::SceneGame() {

}

SceneGame::SceneGame(SceneGame const &copy) {
    *this = copy;
}

SceneGame::~SceneGame() {

}

SceneGame &SceneGame::operator=(SceneGame const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

void SceneGame::eventHandler(std::vector<eEvent> eventList) {
	for (size_t j = 0; j < eventList.size(); j++) {
		if (eventList.at(j) == ECHAP) {
			Nibbler::setCurrentScene(MENU);
		}
	}
}

void SceneGame::drawScene() {
	(*this->_aGraphics)->clear();

	(*this->_aGraphics)->putTexture(GAME_BCKG, 50, 50, Nibbler::getWindowWidth() - 100, Nibbler::getWindowHeight() - 100);
	(*this->_aGraphics)->putTexture(GAME_BORDER, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
	(*this->_aGraphics)->putTexture(SNAKE_H_SMB, 850, 200, 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 48, 200, 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 96, 200, 48, 48);
	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 144, 200, 48, 48);
	(*this->_aGraphics)->putTexture(FOOD, 900, 200, 48, 48);
	(void)this->_food;
	(void)this->_snake;

	(*this->_aGraphics)->display();
}

SceneGame::SceneGame(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
}

void SceneGame::moveSnake() {

}
