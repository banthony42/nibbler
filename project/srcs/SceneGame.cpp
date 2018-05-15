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
int SceneGame::_speed = 7;

SceneGame::SceneGame() {

}

SceneGame::SceneGame(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
	this->_gameInstanced = false;

	this->_snake.headSkin = SceneGame::_selectedHeadSkin;
	this->_snake.bodySkin = SceneGame::_selectedBodySkin;
	this->_snake.vec = {1, 0};
	this->_food = {{10, 10}, FOOD};

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

	this->_snake.speed = SceneGame::_speed;
	this->_snake.vec = {1 * this->_snake.speed, 0 * this->_snake.speed};
	this->_snake.headSkin = SceneGame::_selectedHeadSkin;
	this->_snake.bodySkin = SceneGame::_selectedBodySkin;
	this->_snake.body.clear();
	int y = headPos.y - 1;
	while (++y <= tailPos.y) {
		this->_snake.body.push_back({round(headPos.x), round(y)});
	}
	this->_lastHeadPos = {0, 0};
	this->_headPos = this->_snake.body.at(0);
	this->_score = 0;
}

void SceneGame::initNewFood() {
	t_coordi foodPos = {};
	bool posFound = false;

	while (!posFound) {
		foodPos = {std::rand() % (this->_sectorCount.x), std::rand() % (this->_sectorCount.y)};
		posFound = true;
		for (auto &item : this->_snake.body) {
			if (foodPos.x == item.x && foodPos.y == item.y) {
				posFound = false;
				continue;
			}
		}
	}
	this->_food.pos = {foodPos.x, foodPos.y};
}

void SceneGame::eventHandler(std::vector<eEvent> eventList) {
	for (auto &event : eventList) {
		if (event == ECHAP) {
			this->_gameInstanced = false;
			Nibbler::setCurrentScene(MENU);
		} else if (this->vectorPool.size() < 2) {
			if (event == UP) {
				if (!(this->_snake.vec.x == 0 && this->_snake.vec.y > 0) || this->vectorPool.size()) {
					this->vectorPool.insert(this->vectorPool.cbegin(), {0, -1 * this->_snake.speed});
				}
			}
			if (event == DOWN) {
				if (!(this->_snake.vec.x == 0 && this->_snake.vec.y < 0) || this->vectorPool.size()) {
					this->vectorPool.insert(this->vectorPool.cbegin(), {0, 1 * this->_snake.speed});
				}
			}
			if (event == LEFT) {
				if (!(this->_snake.vec.x > 0 && this->_snake.vec.y == 0) || this->vectorPool.size()) {
					this->vectorPool.insert(this->vectorPool.cbegin(), {-1 * this->_snake.speed, 0});
				}
			}
			if (event == RIGHT) {
				if (!(this->_snake.vec.x < 0 && this->_snake.vec.y == 0) || this->vectorPool.size()) {
					this->vectorPool.insert(this->vectorPool.cbegin(), {1 * this->_snake.speed, 0});
				}
			}
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

	t_coordd sec = this->_snake.body.at(0);
	drawSector(this->_snake.headSkin, sec.x, sec.y);
	int i = 0;
	while (++i <= size) {
		sec = this->_snake.body.at(i);
		drawSector(this->_snake.bodySkin, sec.x, sec.y);
	}
}

void SceneGame::drawFood() {
	drawSector(FOOD, this->_food.pos.x, this->_food.pos.y);
}

void SceneGame::drawOverlay() { // clem : je l'ai rajouté dans l'UML BRAVO ANTHO
	std::string fpsInfo = "fps: " + std::to_string(DeltaTime::fps);
	std::string scoreInfo = "Score: " + std::to_string(this->_score);
	(*this->_aGraphics)->putStrScreen(fpsInfo, PERCENTAGE(20, Nibbler::getWindowWidth()), 40, 1);
	(*this->_aGraphics)->putStrScreen(scoreInfo, PERCENTAGE(75, Nibbler::getWindowWidth()), 40, 1);
}

// TODO faire un ecran pause. Pour le début, pour l'echap, et pour la mort

void SceneGame::moveSnake() {
	t_coordd newPos = this->_headPos;

	newPos.x += (this->_snake.vec.x * DeltaTime::deltaTime);
	newPos.y += (this->_snake.vec.y * DeltaTime::deltaTime);

	if ((Nibbler::iRound(newPos.x) > this->_sectorCount.x - 1) || Nibbler::iRound(newPos.x) < 0 ||
		(Nibbler::iRound(newPos.y) > this->_sectorCount.y - 1) || Nibbler::iRound(newPos.y) < 0) {
		// Collision with wall
		Nibbler::setCurrentScene(GAME_END);
		this->_gameInstanced = false;
		return;
	} else if (Nibbler::iRound(newPos.x) == this->_food.pos.x && Nibbler::iRound(newPos.y) == this->_food.pos.y) {
		// Collision with food
		this->initNewFood();
		t_coordd toInsert = this->_snake.body.at(0);
		this->_snake.body.insert(++this->_snake.body.cbegin(), {toInsert.x, toInsert.y});
		this->_score += 42;
	} else {
		this->_headPos = newPos;
	}
	if (Nibbler::iRound(this->_headPos.x) != Nibbler::iRound((this->_lastHeadPos.x)) ||
		Nibbler::iRound(this->_headPos.y) != Nibbler::iRound((this->_lastHeadPos.y))) {
		if (this->vectorPool.size()) {
			this->_snake.vec = this->vectorPool.back();
			this->vectorPool.pop_back();
		}
		this->_snake.body.insert(this->_snake.body.cbegin(), {round(this->_headPos.x), round(this->_headPos.y)});
		this->_snake.body.pop_back();
		this->_lastHeadPos = this->_snake.body.at(0);
	}
}

void SceneGame::drawScene() {
	(*this->_aGraphics)->clear();
	this->resetSceneGame();
	if (!this->_gameInstanced) {
		this->initNewSnake();
		this->initNewFood();
		this->drawFullSnake();
		this->drawFood();
		this->_score = 0;
		this->_gameInstanced = true;
	} else {
		this->moveSnake();
		this->drawFullSnake();
		this->drawFood();
		this->drawOverlay();
	}
	(*this->_aGraphics)->display();
}

