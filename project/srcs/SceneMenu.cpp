/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneMenu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:59 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:59 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneMenu.hpp"

SceneMenu::SceneMenu() {

}

SceneMenu::SceneMenu(SceneMenu const &copy) {
	*this = copy;
}

SceneMenu::~SceneMenu() {

}

SceneMenu &SceneMenu::operator=(SceneMenu const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

SceneMenu::SceneMenu(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;

	this->_page = PAGE_MENU;
	this->_cursor = MENU_GAME;

	this->_inputName[MENU_GAME] = "Game";
	this->_inputName[MENU_OPTION] = "Options";
	this->_inputName[MENU_EXIT] = "Exit";
	this->_inputName[OPTION_SDL] = "SDL";
	this->_inputName[OPTION_SFML] = "SFML";
	this->_inputName[OPTION_GL] = "OPEN_GL";

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
	pos.x = (*this->_aGraphics)->centerTextX(_inputName[MENU_GAME], SIZE_FONT_MENU, Nibbler::getWindowWidth());
	pos.y = PERCENTAGE(38, Nibbler::getWindowHeight());
	this->_input[MENU_GAME] = pos;
	pos.x = (*this->_aGraphics)->centerTextX(_inputName[OPTION_SDL], SIZE_FONT_MENU, Nibbler::getWindowWidth());
	this->_input[OPTION_SDL] = pos;

	pos.x = (*this->_aGraphics)->centerTextX(_inputName[MENU_OPTION], SIZE_FONT_MENU, Nibbler::getWindowWidth());
	pos.y += FONT_NEWLINE(SIZE_FONT_MENU);
	this->_input[MENU_OPTION] = pos;
	pos.x = (*this->_aGraphics)->centerTextX(_inputName[OPTION_SFML], SIZE_FONT_MENU, Nibbler::getWindowWidth());
	this->_input[OPTION_SFML] = pos;

	pos.x = (*this->_aGraphics)->centerTextX(_inputName[MENU_EXIT], SIZE_FONT_MENU, Nibbler::getWindowWidth());
	pos.y += FONT_NEWLINE(SIZE_FONT_MENU);
	this->_input[MENU_EXIT] = pos;
	pos.x = (*this->_aGraphics)->centerTextX(_inputName[OPTION_GL], SIZE_FONT_MENU, Nibbler::getWindowWidth());
	this->_input[OPTION_GL] = pos;
}

void SceneMenu::eventHandler(std::vector<eEvent> eventList) {
	for (auto &item : eventList) {
		mapEventFuncPtr::iterator it = AScene::_eventMap.find(item);
		if (it == AScene::_eventMap.end()) {
			continue;
		}
		(this->*(this->_eventMap[item]))();
	}
}

void SceneMenu::drawScene() {
	(*this->_aGraphics)->clear();

	// Page du Menu
	if (this->_page == PAGE_MENU) {

		(*this->_aGraphics)->putTexture(MENU_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
		(*this->_aGraphics)->putStrScreen(this->_inputName[MENU_GAME], this->_input[MENU_GAME].x,
										  this->_input[MENU_GAME].y, SIZE_FONT_MENU);
		(*this->_aGraphics)->putStrScreen(this->_inputName[MENU_OPTION], this->_input[MENU_OPTION].x,
										  this->_input[MENU_OPTION].y, SIZE_FONT_MENU);
		(*this->_aGraphics)->putStrScreen(this->_inputName[MENU_EXIT], this->_input[MENU_EXIT].x,
										  this->_input[MENU_EXIT].y, SIZE_FONT_MENU);
	}


	// Page d'options
	if (this->_page == PAGE_OPTION) {

		(*this->_aGraphics)->putTexture(MENU_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
		(*this->_aGraphics)->putStrScreen("Choose a library to run:",
										  (*this->_aGraphics)->centerTextX("Choose a library to run:", SIZE_FONT_MENU,
																		   Nibbler::getWindowWidth()),
										  PERCENTAGE(20, Nibbler::getWindowHeight()),
										  SIZE_FONT_MENU);
		(*this->_aGraphics)->putStrScreen(this->_inputName[OPTION_SDL], this->_input[OPTION_SDL].x,
										  this->_input[OPTION_SDL].y, SIZE_FONT_MENU);
		(*this->_aGraphics)->putStrScreen(this->_inputName[OPTION_SFML], this->_input[OPTION_SFML].x,
										  this->_input[OPTION_SFML].y, SIZE_FONT_MENU);
		(*this->_aGraphics)->putStrScreen(this->_inputName[OPTION_GL], this->_input[OPTION_GL].x,
										  this->_input[OPTION_GL].y, SIZE_FONT_MENU);
	}

	// Draw Cursor
	eMenu curs = static_cast<eMenu>(this->_cursor);
	t_coordi posCurs = {};

	posCurs.x = static_cast<int>(this->_input[curs].x - GET_SIZEFONT_X(SIZE_FONT_MENU));
	posCurs.y = this->_input[curs].y;
	(*this->_aGraphics)->putStrScreen("<", posCurs.x, posCurs.y, SIZE_FONT_MENU);

	posCurs.x = static_cast<int>(this->_input[curs].x +
								 ((this->_inputName[curs].length()) * GET_SIZEFONT_X(SIZE_FONT_MENU)));
	posCurs.y = this->_input[curs].y;
	(*this->_aGraphics)->putStrScreen(">", posCurs.x, posCurs.y, SIZE_FONT_MENU);

	(*this->_aGraphics)->display();
}

void SceneMenu::eventEchap() {
	if (this->_page == PAGE_MENU) {
		Nibbler::_aGraphics->cleanUp();
	} else if (this->_page == PAGE_OPTION) {
		this->_page = PAGE_MENU;
		this->_cursor = MENU_GAME;
	}
}

void SceneMenu::eventUp() {
	if (this->_page == PAGE_MENU) {
		if (this->_cursor > MENU_GAME) {
			this->_cursor--;
		}
	} else if (this->_page == PAGE_OPTION) {
		if (this->_cursor > OPTION_SDL) {
			this->_cursor--;
		}
	}
}

void SceneMenu::eventDown() {
	if (this->_page == PAGE_MENU) {
		if (this->_cursor < MENU_EXIT) {
			this->_cursor++;
		}
	} else if (this->_page == PAGE_OPTION) {
		if (this->_cursor < OPTION_GL) {
			this->_cursor++;
		}
	}
}

void SceneMenu::eventLeft() {}

void SceneMenu::eventRight() {}

void SceneMenu::eventEnter() {
	if (this->_page == PAGE_MENU) {
		if (this->_cursor == MENU_GAME) {
			Nibbler::setCurrentScene(SKIN);
		} else if (this->_cursor == MENU_OPTION) {
			this->_cursor = OPTION_SDL;
			this->_page = PAGE_OPTION;
		} else if (this->_cursor == MENU_EXIT) {
			Nibbler::_aGraphics->cleanUp();
		}
	} else if (this->_page == PAGE_OPTION) {
		if (this->_cursor == OPTION_SDL) {
			Nibbler::loadLibrary(LIB_SDL_PATH);
		} else if (this->_cursor == OPTION_SFML) {
			Nibbler::loadLibrary(LIB_SFML_PATH);
		} else if (this->_cursor == OPTION_GL) {
			Nibbler::loadLibrary(LIB_OPENGL_PATH);
		}
		this->_page = PAGE_MENU;
		this->_cursor = MENU_GAME;
	}
}

void SceneMenu::eventF1() {
	Nibbler::loadLibrary(LIB_SDL_PATH);
}

void SceneMenu::eventF2() {
	Nibbler::loadLibrary(LIB_SFML_PATH);
}

void SceneMenu::eventF3() {
	Nibbler::loadLibrary(LIB_OPENGL_PATH);
}



















