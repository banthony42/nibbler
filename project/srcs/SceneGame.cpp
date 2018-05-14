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

void SceneGame::initNewSnake() {
	t_coordi headPos = {(std::rand() % (this->_sectorCount.x - 3)) + 2,
						(std::rand() % (this->_sectorCount.y - 3))};
	t_coordi tailPos = {headPos.x, headPos.y + 2}; // so the size of 2 + the head so 3

	this->_snake.speed = 2;
	this->_snake.vec = {1 * this->_snake.speed, 0 * this->_snake.speed};
	this->_snake.headSkin = SceneGame::_selectedHeadSkin;
	this->_snake.bodySkin = SceneGame::_selectedBodySkin;
	this->_snake.body.clear();
	int y = headPos.y - 1;
	while (++y <= tailPos.y) {
		this->_snake.body.push_back({round(headPos.x), round(y)});
	}
}

void SceneGame::eventHandler(std::vector<eEvent> eventList) {
	for (size_t j = 0; j < eventList.size(); j++) {
		eEvent e = eventList.at(j);
		if (e == ECHAP) {
			this->_gameInstanced = false;
			Nibbler::setCurrentScene(MENU);
		} else if (e == UP) {
			this->_snake.vec = {0, -1 * this->_snake.speed};
		} else if (e == DOWN) {
			this->_snake.vec = {0, 1 * this->_snake.speed};
		} else if (e == LEFT) {
			this->_snake.vec = {-1 * this->_snake.speed, 0};
		} else if (e == RIGHT) {
			this->_snake.vec = {1 * this->_snake.speed, 0};
		}
	}
}

void SceneGame::drawSector(eTexture t, int sectorX, int sectorY) {
	int posSectorX = this->_sectorStart.x + (this->_sectorSize.x * sectorX);
	int posSectorY = this->_sectorStart.y + (this->_sectorSize.y * sectorY);
	(*this->_aGraphics)->putTexture(t, posSectorX, posSectorY, this->_sectorSize.x, this->_sectorSize.y);
}

void SceneGame::resetSceneGame() {
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
}

// The snake is drawn by the end before, then finish by the head
void SceneGame::drawFullSnake() {
	int size = this->_snake.body.size() - 1;

//	std::cout << "draw new snake :" << std::endl;
//	for (auto &item : this->_snake.body) {
//		std::cout << "snake body x[" << item.x << "]y[" << item.y << "]" << std::endl;
//	}
	t_coordd sec = this->_snake.body.at(0);
	drawSector(this->_snake.headSkin, sec.x, sec.y);
	int i = 0;
	while (++i <= size) {
		sec = this->_snake.body.at(i);
		drawSector(this->_snake.bodySkin, sec.x, sec.y);
	}
}
#include <unistd.h> // TODO to remove

void SceneGame::moveSnake() {
	static t_coordd lastHeadPos = {0, 0};
	static t_coordd headPos = this->_snake.body.at(0);

	headPos.x += (this->_snake.vec.x * DeltaTime::deltaTime);
	headPos.y += (this->_snake.vec.y * DeltaTime::deltaTime);
	if (Nibbler::iRound(headPos.x) != Nibbler::iRound((lastHeadPos.x)) ||
		Nibbler::iRound(headPos.y) != Nibbler::iRound((lastHeadPos.y))) {
        std::cout << "move trigger" << std::endl;
		this->_snake.body.insert(this->_snake.body.cbegin(), {round(headPos.x), round(headPos.y)});
		this->_snake.body.pop_back();
		lastHeadPos = this->_snake.body.at(0);
	}
}

void SceneGame::drawScene() {
	(*this->_aGraphics)->clear();
	this->resetSceneGame();
	if (!this->_gameInstanced) {
		this->initNewSnake();
		this->drawFullSnake();
		this->_gameInstanced = true;
	} else {
		this->moveSnake();
		this->drawFullSnake();
	}
	(*this->_aGraphics)->display();
}