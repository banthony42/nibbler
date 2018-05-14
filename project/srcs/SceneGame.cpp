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

void SceneGame::initSnake() {
	t_coordi headPos = {(std::rand() % (this->_sectorCount.x - 3)) + 2,
						(std::rand() % (this->_sectorCount.y - 3)) + 2};

	t_coordi tailPos = {headPos.x, headPos.y + 2};

	std::vector<t_coordd> snakeBody; // TODO TOTALLY IN PROGRESS BY CLEMENT 
	this->_snake = {snakeBody, 2, {(double)headPos.x, (double)headPos.y}, {(double)tailPos.x, (double)tailPos.y}, {1, 0}, SNAKE_H_PCM, SNAKE_B_PCM};
	this->drawSector(this->_snake.headSkin, static_cast<int>(this->_snake.headPos.x), static_cast<int>(this->_snake.headPos.y));

//	snakeBody().push_back()
}

SceneGame::SceneGame(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
	this->_gameInstanced = false;

//	this->initSnake();
	this->_food = {{10, 10}, 1, FOOD};

	// INIT VAR
	this->_floorSceneStart = {FLOOR_SCENE_START_X, FLOOR_SCENE_START_Y};
	this->_floorSize = {FLOOR_SIZE_X, FLOOR_SIZE_Y};
	// -2 because we don't draw the first line and the last line
	this->_sectorCount = {FLOOR_SIZE_X / SECTOR_DEFAULT_SIZE - 2, FLOOR_SIZE_Y / SECTOR_DEFAULT_SIZE - 2};
	this->_sectorSize = {SECTOR_DEFAULT_SIZE, SECTOR_DEFAULT_SIZE};

	// we add a sector to the sectorSize because we don't draw the first line
	this->_sectorStart.x =
			(this->_floorSceneStart.x) + this->_sectorSize.x + ((FLOOR_SIZE_X % SECTOR_DEFAULT_SIZE) / 2);
	this->_sectorStart.y =
			(this->_floorSceneStart.y) + this->_sectorSize.y + ((FLOOR_SIZE_Y % SECTOR_DEFAULT_SIZE) / 2);
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

void SceneGame::drawSnake() {

}

void SceneGame::drawSector(eTexture t, int sectorX, int sectorY) {
	int posSectorX = this->_sectorStart.x + (this->_sectorSize.x * sectorX);
	int posSectorY = this->_sectorStart.y + (this->_sectorSize.y * sectorY);

	(*this->_aGraphics)->putTexture(t, posSectorX, posSectorY, this->_sectorSize.x, this->_sectorSize.y);
}

void SceneGame::initSceneGame() {
	(*this->_aGraphics)->clear();

	(*this->_aGraphics)->putTexture(GAME_BORDER_GRASS, this->_floorSceneStart.x, this->_floorSceneStart.x,
									this->_floorSize.x, this->_floorSize.y);


	// init the map
	int x = -1;
	while (++x < this->_sectorCount.x) {
		int y = -1;
		while (++y < this->_sectorCount.y) {
			this->drawSector(GAME_GRASS, x, y);

			// TODO is it nece
			// Bordure non jouable pour eviter colision avec GAME_BORDER
//            if (i == 0 || j == 0 || i == this->_sectorCount.x - 1 || j == this->_sectorCount.y - 1)
//                (*this->_aGraphics)->putTexture(GAME_BORDER_GRASS, this->_sectorStart.x + x_increment, this->_sectorStart.y + y_increment,
//                                                this->_sectorSize.x, this->_sectorSize.y);

		}
	}

	// init the snake
//	this->drawSector(this->_snake.headSkin, static_cast<int>(this->_snake.headPos.x), static_cast<int>(this->_snake.headPos.y));

	(*this->_aGraphics)->putTexture(GAME_BORDER, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
	this->initSnake();

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

