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


#include <sstream>
#include <iomanip>
#include "../incl/SceneGame.hpp"

eTexture SceneGame::_selectedHeadSkin = SNAKE_H_PCM;
eTexture SceneGame::_selectedBodySkin = SNAKE_B_PCM;
int SceneGame::_speed = SPEED_DEFAULT;

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
	this->_page = PAGE_GAME;

    // Init Input Name and Position, for page PAUSE
    this->_cursor = RESUME;
    this->_inputName[PAUSE_TITLE] = "PAUSE";
    this->_inputName[RESUME] = "Resume";
    this->_inputName[QUIT] = "Quit";
    t_coordi pos = {};
    pos.x = (*this->_aGraphics)->centerTextX(this->_inputName[PAUSE_TITLE], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    pos.y = PERCENTAGE(20, Nibbler::getWindowHeight());
    this->_input[PAUSE_TITLE] = pos;
    pos.x = (*this->_aGraphics)->centerTextX(this->_inputName[RESUME], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    pos.y = PERCENTAGE(45, Nibbler::getWindowHeight());
    this->_input[RESUME] = pos;
    pos.x = (*this->_aGraphics)->centerTextX(this->_inputName[QUIT], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    pos.y += FONT_NEWLINE(SIZE_FONT_MENU);
    this->_input[QUIT] = pos;
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

// memo : head is the begin
void SceneGame::initNewSnake() {
	t_coordi headPos = {(std::rand() % (this->_sectorCount.x - 3)) + 2,
						(std::rand() % (this->_sectorCount.y - 4)) + 3};
	t_coordi tailPos = {headPos.x, headPos.y + 2};

	this->_snake.speed = SPEED_DEFAULT;
	this->_snake.vec = {0 * this->_snake.speed, -1 * this->_snake.speed};
	this->_snake.headSkin = SceneGame::_selectedHeadSkin;
	this->_snake.bodySkin = SceneGame::_selectedBodySkin;
	this->_snake.body.clear();
	int y = headPos.y - 1;
	while (++y <= tailPos.y) {
		this->_snake.body.insert(this->_snake.body.cend(), {round(headPos.x), round(y)});
	}
	this->_lastHeadPos = this->_snake.body.front();
	this->_headPos = this->_snake.body.front();
	this->_score = 0;
//	std::cout << "snake :" << std::endl;
//	for (auto &item : this->_snake.body) {
//		std::cout << "x: " << item.x << " y: " << item.y << std::endl;
//	}
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
	if (this->_page == PAGE_GAME) {
		for (auto &event : eventList) {
			if (event == ECHAP) {
				this->_page = PAGE_PAUSE;
			} else if (this->vectorPool.size() < 2) {
				if (event == UP) {
					if (!(this->_snake.vec.x == 0 && this->_snake.vec.y > 0) || this->vectorPool.size()) {
						this->vectorPool.insert(this->vectorPool.cbegin(), {0, -1 * this->_snake.speed});
					}
				} else if (event == DOWN) {
					if (!(this->_snake.vec.x == 0 && this->_snake.vec.y < 0) || this->vectorPool.size()) {
						this->vectorPool.insert(this->vectorPool.cbegin(), {0, 1 * this->_snake.speed});
					}
				} else if (event == LEFT) {
					if (!(this->_snake.vec.x > 0 && this->_snake.vec.y == 0) || this->vectorPool.size()) {

						this->vectorPool.insert(this->vectorPool.cbegin(), {-1 * this->_snake.speed, 0});
					}
				} else if (event == RIGHT) {
					if (!(this->_snake.vec.x < 0 && this->_snake.vec.y == 0) || this->vectorPool.size()) {
						this->vectorPool.insert(this->vectorPool.cbegin(), {1 * this->_snake.speed, 0});
					}
				}
			}
		}
	} else if (this->_page == PAGE_PAUSE) {
		for (auto &event : eventList) {
			if (event == UP && this->_cursor > RESUME) {
                this->_cursor--;
            } else if (event == DOWN && this->_cursor < QUIT) {
                this->_cursor++;
            } else if (event == ENTER) {
                if (this->_cursor == RESUME) {
                    this->_page = PAGE_GAME;
                } else if (this->_cursor == QUIT) {
                    this->_gameInstanced = false;
                    Nibbler::setCurrentScene(MENU);
                    this->_page = PAGE_GAME;
                }
            }
		}
	} else if (this->_page == PAGE_GAMEOVER) {
		for (auto &event : eventList) {
            if (event == ECHAP) {
                this->_gameInstanced = false;
                Nibbler::setCurrentScene(MENU);
                this->_page = PAGE_GAME;
            }
			else if (event == ENTER) {
				this->_gameInstanced = false;
				this->_page = PAGE_GAME;
				Nibbler::setCurrentScene(GAME_END);
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

void SceneGame::drawInfoOverlay() { // clem : je l'ai rajouté dans l'UML BRAVO ANTHO
	std::string fpsInfo = "fps: " + std::to_string(DeltaTime::fps);
	std::string scoreInfo = "Score: " + std::to_string(this->_score);
    // Obliger pour pouvoir regler la precision, car to_string affiche 1.000000
    std::ostringstream speedInfo;
    speedInfo << "Speed x " << std::setprecision(2) << this->_difficulty;
	(*this->_aGraphics)->putStrScreen(fpsInfo, PERCENTAGE(20, Nibbler::getWindowWidth()), 40, 1);
	(*this->_aGraphics)->putStrScreen(scoreInfo, PERCENTAGE(80, Nibbler::getWindowWidth()), 40, 1);
    (*this->_aGraphics)->putStrScreen(speedInfo.str(), PERCENTAGE(62, Nibbler::getWindowWidth()), 40, 1);
}

// TODO faire un ecran pause. Pour le début, pour l'echap, et pour la mort
// TODO quand on bourrine toute les touches en meme temps une collision pop au debut alors que le snake fait une taille de 4
// => parfois le GameOver pop en faisant replay, reset sur des valeurs de vecteur a faire ?

bool SceneGame::checkCollision(t_coordi pos) {
	// Collision with wall
	if ((pos.x > this->_sectorCount.x - 1) || pos.x < 0 ||
		(pos.y > this->_sectorCount.y - 1) || pos.y < 0) {
		return true;
	}

	// Collision with himself
	int i = 0;
	int max = this->_snake.body.size();
	while (++i < max) {
		auto item = this->_snake.body.at(i);
		if (pos.x == Nibbler::iRound(item.x) && pos.y == Nibbler::iRound(item.y)) {
			return true;
		}
	}

	// Collision with food
	if (pos.x == this->_food.pos.x && pos.y == this->_food.pos.y) {
		this->initNewFood();
		t_coordd toInsert = this->_snake.body.at(0);
		this->_snake.body.insert(++this->_snake.body.cbegin(), {toInsert.x, toInsert.y});
		this->_score += 42;
        if (!(this->_score % SPEED_INCR)) {
            this->_difficulty += DIFFICULTY_INCR;
            this->_snake.speed = SceneGame::_speed * this->_difficulty;
            std::cout << "New speed:" << SceneGame::_speed << std::endl;
        }
	}
	return false;
}


void SceneGame::moveSnake() {
	t_coordd newPos = this->_headPos;

	newPos.x += (this->_snake.vec.x * DeltaTime::deltaTime);
	newPos.y += (this->_snake.vec.y * DeltaTime::deltaTime);

	if (this->checkCollision({Nibbler::iRound(newPos.x), Nibbler::iRound(newPos.y)})) {
		this->_page = PAGE_GAMEOVER;
	} else {
		this->_headPos = newPos;
	}
	if (Nibbler::iRound(this->_headPos.x) != Nibbler::iRound((this->_lastHeadPos.x)) ||
		Nibbler::iRound(this->_headPos.y) != Nibbler::iRound((this->_lastHeadPos.y))) {
		// Move the snake
		if (this->vectorPool.size()) {
			this->_snake.vec = this->vectorPool.back();
			this->vectorPool.pop_back();
		}
		this->_snake.body.insert(this->_snake.body.cbegin(), {round(this->_headPos.x), round(this->_headPos.y)});
		this->_snake.body.pop_back();
		this->_lastHeadPos = this->_snake.body.at(0);
	}
}

void SceneGame::drawPauseOverlay() {
    (*this->_aGraphics)->putTexture(FOG_OVERLAY, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
    (*this->_aGraphics)->putStrScreen(this->_inputName[PAUSE_TITLE], this->_input[PAUSE_TITLE].x, this->_input[PAUSE_TITLE].y, SIZE_FONT_MENU);
    (*this->_aGraphics)->putStrScreen(this->_inputName[RESUME], this->_input[RESUME].x, this->_input[RESUME].y, SIZE_FONT_MENU);
    (*this->_aGraphics)->putStrScreen(this->_inputName[QUIT], this->_input[QUIT].x, this->_input[QUIT].y, SIZE_FONT_MENU);

    // Draw Cursor
    ePause curs = static_cast<ePause>(this->_cursor);
    t_coordi posCurs = {};

    posCurs.x = static_cast<int>(this->_input[curs].x - GET_SIZEFONT_X(SIZE_FONT_MENU));
    posCurs.y = this->_input[curs].y;
    (*this->_aGraphics)->putStrScreen("<", posCurs.x, posCurs.y, SIZE_FONT_MENU);
    posCurs.x = static_cast<int>(this->_input[curs].x + ((this->_inputName[curs].length()) * GET_SIZEFONT_X(SIZE_FONT_MENU)));
    posCurs.y = this->_input[curs].y;
    (*this->_aGraphics)->putStrScreen(">", posCurs.x, posCurs.y, SIZE_FONT_MENU);
}

void SceneGame::drawGameOverOverlay() {
    std::string gameOverMessage = "GAME OVER";
    std::string scoreInfo = "Score:" + std::to_string(this->_score);
    std::string quitInfo = "Press ENTER";
    t_coordi pos = {};

    (*this->_aGraphics)->putTexture(GAMEOVER_BORDER, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
    pos.x = (*this->_aGraphics)->centerTextX(gameOverMessage, SIZE_FONT_MENU, Nibbler::getWindowWidth());
    pos.y = PERCENTAGE(45, Nibbler::getWindowHeight());
    (*this->_aGraphics)->putStrScreen(gameOverMessage, pos.x, pos.y, SIZE_FONT_MENU);
    pos.x = (*this->_aGraphics)->centerTextX(scoreInfo, SIZE_FONT_GAMEOVER, Nibbler::getWindowWidth());
    pos.y += FONT_NEWLINE(SIZE_FONT_MENU);
    (*this->_aGraphics)->putStrScreen(scoreInfo, pos.x, pos.y, SIZE_FONT_GAMEOVER);
    pos.x = (*this->_aGraphics)->centerTextX(quitInfo, SIZE_FONT_GAMEOVER, Nibbler::getWindowWidth());
    pos.y = PERCENTAGE(75, Nibbler::getWindowHeight());

    if (this->_timestamp > this->_deltaTimeCount) {
        this->_timestamp = 0;
    }
    if (this->_timestamp < (this->_deltaTimeCount / 2))
        (*this->_aGraphics)->putStrScreen(quitInfo, pos.x, pos.y, SIZE_FONT_GAMEOVER);
    this->_timestamp += (DeltaTime::elapsedTime);
}

void SceneGame::drawScene() {
	(*this->_aGraphics)->clear();
	//  TODO optimiser le code pour pas ecrir 3 fois la meme sequence de draw si possible
	if (this->_page == PAGE_GAME) {
		this->resetSceneGame();
		if (!this->_gameInstanced) {
			this->initNewSnake();
			this->initNewFood();
			this->drawFullSnake();
			this->drawFood();
			this->_score = 0;
            this->_difficulty = 1;
            this->_deltaTimeCount = 1000;
            this->_timestamp = 0;
            this->vectorPool.clear();
			this->_gameInstanced = true;
		} else {
			this->moveSnake();
			this->drawFullSnake();
			this->drawFood();
			this->drawInfoOverlay();
		}
	} else if (this->_page == PAGE_PAUSE) {
		this->resetSceneGame();
		this->drawFullSnake();
		this->drawFood();
		this->drawInfoOverlay();
        this->drawPauseOverlay();
	} else if (this->_page == PAGE_GAMEOVER) {
		this->resetSceneGame();
		this->drawFullSnake();
		this->drawFood();
		this->drawInfoOverlay();
        this->drawGameOverOverlay();
	}
	(*this->_aGraphics)->display();
}

