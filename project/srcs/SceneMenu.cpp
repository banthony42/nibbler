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

SceneMenu::SceneMenu(AGraphics **aGraphics) {
	this->_aGraphics = aGraphics;

	// Permet d'afficher soit le menu principal (page 1), soit les options(page 2) dans la meme scene
	this->_page = PAGE_MENU;

	// Index du tableau d'input, permet d'afficher le curseur de selection
	this->_cursor = MENU_GAME;

	// Tableau d'input
	t_coordi pos = {};
	pos.x = (*this->_aGraphics)->centerTextX("Game", SIZE_FONT_MENU, Nibbler::getWindowWidth());
	pos.y = PERCENTAGE(38, Nibbler::getWindowHeight());
	this->_input[MENU_GAME] = pos;

	pos.x = (*this->_aGraphics)->centerTextX("Options", SIZE_FONT_MENU, Nibbler::getWindowWidth());
	pos.y += FONT_NEWLINE;
	this->_input[MENU_OPTION] = pos;

	pos.x = (*this->_aGraphics)->centerTextX("Exit", SIZE_FONT_MENU, Nibbler::getWindowWidth());
	pos.y += FONT_NEWLINE;
	this->_input[MENU_EXIT] = pos;

	this->_inputName[MENU_GAME] = "Game";
	this->_inputName[MENU_OPTION] = "Options";
	this->_inputName[MENU_EXIT] = "Exit";
}

SceneMenu &SceneMenu::operator=(SceneMenu const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

void SceneMenu::eventHandler(std::vector<eEvent> eventList) { // TODO solve the problem of repeating

	if (this->_page == PAGE_MENU) {
		for (size_t j = 0; j < eventList.size(); j++) {
			if (eventList.at(j) == ECHAP) {
				Nibbler::_aGraphics->cleanUp();
			}
			if (eventList.at(j) == UP) {
				if (this->_cursor > MENU_GAME)
					this->_cursor--;
			}
			if (eventList.at(j) == DOWN) {
				if (this->_cursor < MENU_EXIT)
					this->_cursor++;
			}
			if (eventList.at(j) == ENTER) {
				if (this->_cursor == MENU_GAME)
					Nibbler::setCurrentScene(GAME);
				else if (this->_cursor == MENU_OPTION)
					this->_page = 2;
				else if (this->_cursor == MENU_EXIT)
					Nibbler::_aGraphics->cleanUp();
			}
		}
	}
	if (this->_page == PAGE_OPTION) {
		for (size_t j = 0; j < eventList.size(); j++) {
			if (eventList.at(j) == ECHAP) {
				this->_page = 1;
			}
			if (eventList.at(j) == RIGHT) {
				Nibbler::loadLibrary(LIB_SDL_PATH);
			}
			if (eventList.at(j) == LEFT) {
				Nibbler::loadLibrary(LIB_SFML_PATH);
			}
			if (eventList.at(j) == UP) {
				Nibbler::loadLibrary(LIB_OPENGL_PATH);
			}
		}
	}
}

// TODO griser la lib utilisé dans la selection des libs
void SceneMenu::drawScene() {
	(*this->_aGraphics)->clear();

	// Page du Menu
	if (this->_page == PAGE_MENU) {

			(*this->_aGraphics)->putTexture(MENU_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
		(*this->_aGraphics)->putStrScreen("Game", this->_input[MENU_GAME].x, this->_input[MENU_GAME].y, SIZE_FONT_MENU);
		(*this->_aGraphics)->putStrScreen("Options", this->_input[MENU_OPTION].x, this->_input[MENU_OPTION].y, SIZE_FONT_MENU);
		(*this->_aGraphics)->putStrScreen("Exit", this->_input[MENU_EXIT].x, this->_input[MENU_EXIT].y, SIZE_FONT_MENU);

		// Draw Cursor
		eMenu curs = static_cast<eMenu>(this->_cursor);
		t_coordi posCurs = {};

		posCurs.x = static_cast<int>(this->_input[curs].x - GET_SIZEFONT_X(SIZE_FONT_MENU));
		posCurs.y = this->_input[curs].y;
		(*this->_aGraphics)->putStrScreen("<", posCurs.x, posCurs.y, SIZE_FONT_MENU);

		posCurs.x = static_cast<int>(this->_input[curs].x + ((this->_inputName[curs].length()) * GET_SIZEFONT_X(SIZE_FONT_MENU)));
		posCurs.y = this->_input[curs].y;
		(*this->_aGraphics)->putStrScreen(">", posCurs.x, posCurs.y, SIZE_FONT_MENU);
	}


	// Page d'options
	if (this->_page == PAGE_OPTION) {

	}

	(*this->_aGraphics)->display();

//	// Preview des Scenes
//	// Déso j'avais plus trop le temps les positions sont hard codé parfois, pour un ecran de 1200 x 900
//
//	// MENU preview
//	(*this->_aGraphics)->putTexture(MENU_BCKG, 0, 0, Nibbler::getWindowWidth() / 2, Nibbler::getWindowHeight() / 2);
//	(*this->_aGraphics)->putStrScreen("< Game >", (Nibbler::getWindowWidth() / 4) - (4 * 32), 150, 2);
//	(*this->_aGraphics)->putStrScreen("Options", (Nibbler::getWindowWidth() / 4) - (3 * 32), 200, 2);
//	(*this->_aGraphics)->putStrScreen("Exit", (Nibbler::getWindowWidth() / 4) - (2 * 32), 250, 2);
//
//	// GAME preview
//	(*this->_aGraphics)->putTexture(GAME_BCKG, (Nibbler::getWindowWidth() / 2) + 25, 25, (Nibbler::getWindowWidth() / 2) - 50, (Nibbler::getWindowHeight() / 2) - 50);
//	(*this->_aGraphics)->putTexture(GAME_BORDER, Nibbler::getWindowWidth() / 2, 0, Nibbler::getWindowWidth() / 2, Nibbler::getWindowHeight() / 2);
//	(*this->_aGraphics)->putTexture(SNAKE_H_SMB, 850, 200, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 24, 200, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 48, 200, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 850 - 72, 200, 24, 24);
//	(*this->_aGraphics)->putTexture(FOOD, 900, 200, 24, 24);
//
//	// SKIN selection preview
//	(*this->_aGraphics)->putTexture(SKIN_FRAME, 0, Nibbler::getWindowHeight() / 2, Nibbler::getWindowWidth() / 2, Nibbler::getWindowHeight() / 2);
//	(*this->_aGraphics)->putStrScreen("<               >", 330 - (8 * 32), 490, 2);
//	(*this->_aGraphics)->putTexture(SNAKE_H_PCM, 330, 500, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, 330 - 24, 500, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, 330 - 48, 500, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_PCM, 330 - 72, 500, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_H_SMB, 330, 655, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 330 - 24, 655, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 330 - 48, 655, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_SMB, 330 - 72, 655, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_H_HK, 330, 810, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_HK, 330 - 24, 810, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_HK, 330 - 48, 810, 24, 24);
//	(*this->_aGraphics)->putTexture(SNAKE_B_HK, 330 - 72, 810, 24, 24);
//
//	// GAME END preview
//	(*this->_aGraphics)->putTexture(SCORE_BCKG, Nibbler::getWindowWidth() / 2, Nibbler::getWindowHeight() / 2, Nibbler::getWindowWidth() / 2, Nibbler::getWindowHeight() / 2);
//	(*this->_aGraphics)->putStrScreen("GAME OVER", (900) - (4 * 32), 550, 2);
//	(*this->_aGraphics)->putStrScreen("Score: 1542", (900) - (5 * 32), 600, 2);
//	(*this->_aGraphics)->putStrScreen("< Replay >", (900) - (5 * 32), 700, 2);
//	(*this->_aGraphics)->putStrScreen("Menu", (900) - (3 * 32), 750, 2);
//
//	/*
//	// GAME Fullscreen preview, dé-commenté pour un apercu du jeu sur tout l'ecran
//	(*this->_aGraphics)->clear();
//	(*this->_aGraphics)->putTexture(GAME_BCKG, 50, 50, Nibbler::getWindowWidth() - 100, Nibbler::getWindowHeight() - 100);
//	(*this->_aGraphics)->putTexture(BORDER, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
//	*/
//	(*this->_aGraphics)->display();
}




















