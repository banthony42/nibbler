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
#include "../incl/AGraphics.hpp"

eTexture SceneGame::_selectedHeadSkin = SNAKE_H_PCM;
eTexture SceneGame::_selectedBodySkin = SNAKE_B_PCM;

SceneGame::SceneGame() {

}

SceneGame::SceneGame(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
	this->_gameInstanced = false;
	this->_floorSceneStart = {FLOOR_SCENE_START_X, FLOOR_SCENE_START_Y};
	this->_floorSceneEnd = {FLOOR_SCENE_END_X, FLOOR_SCENE_END_Y};
	this->_sectorStart = {SECTOR_START_X, SECTOR_START_Y};
	this->_sectorCount = {FLOOR_SIZE_X / SECTOR_DEFAULT_SIZE_X - 1, FLOOR_SIZE_Y / SECTOR_DEFAULT_SIZE_Y - 1};
	this->_sectorSize = {SECTOR_DEFAULT_SIZE_X, SECTOR_DEFAULT_SIZE_Y};

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
			this->_gameInstanced = false;
			Nibbler::setCurrentScene(MENU);
		}
	}
}

void SceneGame::initSceneGame() {
	(*this->_aGraphics)->clear();

	(*this->_aGraphics)->putTexture(GAME_GRASS, this->_sectorStart.x, this->_sectorStart.y,
									this->_sectorSize.x, this->_sectorSize.y);

	(*this->_aGraphics)->putTexture(GAME_BORDER_GRASS, this->_floorSceneStart.x, this->_floorSceneStart.x,
									this->_floorSceneEnd.x, this->_floorSceneEnd.y);

	(*this->_aGraphics)->putTexture(GAME_BORDER, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());


	int i = -1;
	while (++i < this->_sectorCount.x) {
		int x_increment = this->_sectorSize.x * i;
		int j = -1;
		while (++j < this->_sectorCount.y) {
			int y_increment = this->_sectorSize.y * j;
			(*this->_aGraphics)->putTexture(GAME_GRASS, this->_sectorStart.x + x_increment, this->_sectorStart.y + y_increment,
											this->_sectorSize.x, this->_sectorSize.y);

		}
	}



//	this->floorSceneStartX



//	(*this->_aGraphics)->putTexture(SNAKE_H_SMB, 850, 200, 48, 48);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 48, 200, 48, 48);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 96, 200, 48, 48);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 144, 200, 48, 48);
//	(*this->_aGraphics)->putTexture(FOOD, 900, 200, 48, 48);
	this->_gameInstanced = true;
	(*this->_aGraphics)->display();
	std::cout << "init game" << std::endl;
}

void SceneGame::drawScene() {
//	(*this->_aGraphics)->clear();
	if (!this->_gameInstanced) {
		this->initSceneGame();
	}

	(void) this->_food;
	(void) this->_snake;
//	(*this->_aGraphics)->display();
}

void SceneGame::moveSnake() {

}

