/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneGameEnd.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:54 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:54 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneGameEnd.hpp"

SceneGameEnd::SceneGameEnd() {

}

SceneGameEnd::SceneGameEnd(SceneGameEnd const &copy) {
	*this = copy;
}

SceneGameEnd::~SceneGameEnd() {

}

SceneGameEnd::SceneGameEnd(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;
	this->_cursor = REPLAY;
	this->_inputName[BEST_SCORE] = "Best Score:" + std::to_string(SceneGame::_bestScore);
	this->_inputName[REPLAY] = "Replay";
	this->_inputName[BACK_TO_MENU] = "Menu";

	this->_eventMap[ECHAP] = &AScene::eventEchap;
	this->_eventMap[UP] = &AScene::eventUp;
	this->_eventMap[DOWN] = &AScene::eventDown;
	this->_eventMap[LEFT] = &AScene::eventLeft;
	this->_eventMap[RIGHT] = &AScene::eventRight;
	this->_eventMap[ENTER] = &AScene::eventEnter;
	this->_eventMap[F1] = &AScene::eventF1;
	this->_eventMap[F2] = &AScene::eventF2;
	this->_eventMap[F3] = &AScene::eventF3;

	t_coordi pos = {};
	pos.x = PERCENTAGE(62, Nibbler::getWindowWidth());
	pos.y = PERCENTAGE(59, Nibbler::getWindowHeight());
	this->_input[BEST_SCORE] = pos;
	pos.x += PERCENTAGE(3, Nibbler::getWindowWidth());
	pos.y += FONT_NEWLINE(SIZE_FONT_GAME_END) * 2;
	this->_input[REPLAY] = pos;
	pos.x += ((this->_inputName[REPLAY].length() - this->_inputName[BACK_TO_MENU].length()) / 2) *
			 GET_SIZEFONT_X(SIZE_FONT_GAME_END);
	pos.y += FONT_NEWLINE(SIZE_FONT_GAME_END);
	this->_input[BACK_TO_MENU] = pos;
}

SceneGameEnd &SceneGameEnd::operator=(SceneGameEnd const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

void SceneGameEnd::eventHandler(std::vector<eEvent> eventList) {
	for (auto &item : eventList) {
		mapEventFuncPtr::iterator it = AScene::_eventMap.find(item);
		if (it == AScene::_eventMap.end()) {
			continue;
		}
		(this->*(this->_eventMap[item]))();
	}
}

void SceneGameEnd::drawScene() {
	(*this->_aGraphics)->clear();
	this->_inputName[BEST_SCORE] = "Best Score:" + std::to_string(SceneGame::_bestScore);

	(*this->_aGraphics)->putTexture(SCORE_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
	(*this->_aGraphics)->putStrScreen(this->_inputName[BEST_SCORE], this->_input[BEST_SCORE].x,
									  this->_input[BEST_SCORE].y + 20, SIZE_FONT_GAME_END);
	(*this->_aGraphics)->putStrScreen(this->_inputName[REPLAY], this->_input[REPLAY].x, this->_input[REPLAY].y,
									  SIZE_FONT_GAME_END);
	(*this->_aGraphics)->putStrScreen(this->_inputName[BACK_TO_MENU], this->_input[BACK_TO_MENU].x,
									  this->_input[BACK_TO_MENU].y, SIZE_FONT_GAME_END);

	// Draw Cursor
	eEndGame curs = static_cast<eEndGame >(this->_cursor);
	t_coordi posCurs = {};

	posCurs.x = static_cast<int>(this->_input[curs].x - GET_SIZEFONT_X(SIZE_FONT_GAME_END));
	posCurs.y = this->_input[curs].y;
	(*this->_aGraphics)->putStrScreen("<", posCurs.x, posCurs.y, SIZE_FONT_GAME_END);
	posCurs.x = static_cast<int>(this->_input[curs].x +
								 ((this->_inputName[curs].length()) * GET_SIZEFONT_X(SIZE_FONT_GAME_END)));
	posCurs.y = this->_input[curs].y;
	(*this->_aGraphics)->putStrScreen(">", posCurs.x, posCurs.y, SIZE_FONT_GAME_END);

	(*this->_aGraphics)->display();
}

void SceneGameEnd::eventEchap() {
	Nibbler::setCurrentScene(MENU);
}

void SceneGameEnd::eventUp() {
	if (this->_cursor > REPLAY) {
		this->_cursor--;
	}
}

void SceneGameEnd::eventDown() {
	if (this->_cursor < BACK_TO_MENU) {
		this->_cursor++;
	}
}

void SceneGameEnd::eventLeft() {}

void SceneGameEnd::eventRight() {}

void SceneGameEnd::eventEnter() {
	if (this->_cursor == REPLAY) {
		Nibbler::setCurrentScene(GAME);
	} else if (this->_cursor == BACK_TO_MENU) {
		Nibbler::setCurrentScene(MENU);
	}
	this->_cursor = REPLAY;
}

void SceneGameEnd::eventF1() {
	Nibbler::libToLoad = LIB_SDL_PATH;
}

void SceneGameEnd::eventF2() {
	Nibbler::libToLoad = LIB_SFML_PATH;
}

void SceneGameEnd::eventF3() {
	Nibbler::libToLoad = LIB_OPENGL_PATH;
}
