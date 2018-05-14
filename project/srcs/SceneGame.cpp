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

void SceneGame::initNewSnake() {
	t_coordi headPos = {(std::rand() % (this->_sectorCount.x - 3)) + 2,
						(std::rand() % (this->_sectorCount.y - 3))};
	t_coordi tailPos = {headPos.x, headPos.y + 2}; // so the size of 2 + the head so 3

	this->_snake.headPos = {round(headPos.x), round(headPos.y)};
	this->_snake.tailPos = {round(tailPos.x), round(tailPos.y)};
	this->_snake.vec = {1, 0};
	this->_snake.headSkin = SceneGame::_selectedHeadSkin;
	this->_snake.bodySkin = SceneGame::_selectedBodySkin;
	this->_snake.body.clear();
	int y = headPos.y - 1;
	while (++y <= tailPos.y) {
		this->_snake.body.push_back({round(headPos.x), round(y)});
	}
}

SceneGame::SceneGame(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
	this->_gameInstanced = false;

//	this->initSnake();
	this->_snake.headSkin = SceneGame::_selectedHeadSkin;
	this->_snake.bodySkin = SceneGame::_selectedBodySkin;
	this->_snake.vec = {1, 0};
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
		eEvent e = eventList.at(j);
		if (e == ECHAP) {
			this->_gameInstanced = false;
			Nibbler::setCurrentScene(MENU);
		} else if (e == UP) {
			this->_snake.vec = {0, -1};
		} else if (e == DOWN) {
			this->_snake.vec = {0, 1};
		} else if (e == LEFT) {
			this->_snake.vec = {-1, 0};
		} else if (e == RIGHT) {
			this->_snake.vec = {1, 0};
		}
	}
}

// The snake is drawn by the end before, then finish by the head
void SceneGame::drawFullSnake() {
	int size = this->_snake.body.size() - 1;

	t_coordd sec = this->_snake.body.at(0);
	drawSector(this->_snake.headSkin, sec.x, sec.y);
	int i = 0;
	while (++i <= size) {
		sec = this->_snake.body.at(i);
		drawSector(this->_snake.bodySkin, sec.x, sec.y);
	}
}

void SceneGame::drawRecycledSnake() {

	auto begin = this->_snake.body.cbegin();
	auto end = this->_snake.body.back();

	drawSector(GAME_GRASS, end.x, end.y);
	drawSector(this->_snake.headSkin, begin->x, begin->y);
	begin++;
	drawSector(GAME_GRASS, begin->x, begin->y);
	drawSector(this->_snake.bodySkin, begin->x, begin->y);
	this->_snake.body.pop_back();
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
		}
	}
	(*this->_aGraphics)->putTexture(GAME_BORDER, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
	this->_gameInstanced = true;
	(*this->_aGraphics)->display();
	std::cout << "init game" << std::endl;
}

void SceneGame::moveSnake() {
	auto coordOfHead = this->_snake.body.at(0);
	this->_snake.body.insert(this->_snake.body.cbegin(), {coordOfHead.x + this->_snake.vec.x, coordOfHead.y + this->_snake.vec.y});
}

#include <unistd.h>
void SceneGame::drawScene() {
	if (!this->_gameInstanced) {
		this->initSceneGame();
		this->initSceneGame();
		this->initNewSnake();
		this->drawFullSnake();
		(*this->_aGraphics)->display();
	} else {
		usleep(500000);
		this->moveSnake();
		this->drawRecycledSnake();
		(*this->_aGraphics)->display();
	}
}



