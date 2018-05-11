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

eTexture SceneGame::_selectedHeadSkin = SNAKE_H_PCM;
eTexture SceneGame::_selectedBodySkin = SNAKE_B_PCM;

SceneGame::SceneGame() {

}

SceneGame::SceneGame(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
	this->_gameInstanced = false;
	this->_floorSceneStart = {FLOOR_SCENE_START_X, FLOOR_SCENE_START_Y};
	this->_floorSceneEnd = {FLOOR_SCENE_END_X, FLOOR_SCENE_END_Y};

    this->_sectorSize =  SECTOR_MINI_SIZE;

    int min = FLOOR_SIZE_Y;
    if (FLOOR_SIZE_X < FLOOR_SIZE_Y)
        min = FLOOR_SIZE_X;

    while ((min % this->_sectorSize)) {
        this->_sectorSize++;
    }

    this->_sectorCount = min / this->_sectorSize;

    std::cout << FLOOR_SIZE_X << " * " << FLOOR_SIZE_Y << " min: "<< min << std::endl;
    std::cout << this->_sectorSize << " * " << this->_sectorCount << " = " << (this->_sectorSize * this->_sectorCount) << std::endl;
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

    (*this->_aGraphics)->putTexture(GAME_BORDER, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
    (*this->_aGraphics)->putTexture(GAME_BORDER_GRASS, this->_floorSceneStart.x, this->_floorSceneStart.y,  FLOOR_SIZE_X,  FLOOR_SIZE_Y);

    t_coordi incr = {};
    t_coordi pos = {};

    while (incr.y < this->_sectorCount) {
        incr.x = 0;

        pos.y = this->_floorSceneStart.y + ( incr.y * this->_sectorSize);
        while (incr.x < this->_sectorCount) {
            pos.x = this->_floorSceneStart.x +  (incr.x * this->_sectorSize);

//            (*this->_aGraphics)->putTexture(GAME_GRASS, pos.x, pos.y, this->_sectorSize, this->_sectorSize);

            incr.x++;
        }
        incr.y++;
    }

    std::cout << incr.x << " - " << incr.y << std::endl;



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

